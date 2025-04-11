package org.example.bookmanagement_springboot.service.impl;

import com.baomidou.mybatisplus.core.conditions.query.LambdaQueryWrapper;
import com.baomidou.mybatisplus.extension.conditions.query.LambdaQueryChainWrapper;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.example.bookmanagement_springboot.dto.BookDTO;
import org.example.bookmanagement_springboot.entity.Book;
import org.example.bookmanagement_springboot.enums.ResultEnum;
import org.example.bookmanagement_springboot.exception.BusinessException;
import org.example.bookmanagement_springboot.mapper.BookMapper;
import org.example.bookmanagement_springboot.service.BookService;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.List;

/**
* @author DELL
* @description 针对表【book】的数据库操作Service实现
* @createDate 2025-03-27 22:04:17
*/
@Service
@Transactional(rollbackFor = Exception.class)
@RequiredArgsConstructor
@Slf4j
public class BookServiceImpl extends ServiceImpl<BookMapper, Book> implements BookService {

    private final BookMapper bookMapper;
    
    public Book add(BookDTO bookDTO){
        // 1. 检查图书ID是否存在
        if (lambdaQuery()
                .eq(Book::getBookId, bookDTO.getBookId())
                .exists()) {
            log.warn("图书已存在，图书ID: {}", bookDTO.getBookId());
            throw new BusinessException(ResultEnum.BOOK_ID_CONFLICT);
        }
        try {
            // 2. 创建新图书
            Book book = new Book()
                    .setBookId(bookDTO.getBookId())
                    .setTitle(bookDTO.getTitle())
                    .setAuthor(bookDTO.getAuthor())
                    .setPublisher(bookDTO.getPublisher())
                    .setPublishDate(bookDTO.getPublishDate());


            // 3. 保存图书
            if (!save(book)) {
                log.error("图书保存失败，图书信息: {}", bookDTO);
                throw new BusinessException(ResultEnum.BOOK_ADD_ERROR);
            }
            return book;
        } catch (BusinessException e) {
            throw e; // 已知业务异常直接抛出
        } catch (Exception e) {
            log.error("添加图书时发生系统异常", e);
            throw new BusinessException(ResultEnum.SYSTEM_ERROR, "图书添加失败");
        }
    }

    @Override
    public Boolean deleteById(String bookId){
        try {
            Book book = lambdaQuery().eq(Book::getBookId, bookId).one();
            if (book != null) {
                bookMapper.deleteById(book.getBookId());
                return true;
            }else{
                return false;
            }
        } catch (Exception e) {
            log.error("删除图书时发生系统异常", e);
            throw new BusinessException(ResultEnum.BOOK_DELETE_ERROR, "图书删除失败");
        }
    }

    @Override
    public Boolean deleteBooks(List<String> bookIds){
        try {
            for(String bookId : bookIds){
                Book book = lambdaQuery().eq(Book::getBookId, bookId).one();
                if (book != null ) {
                    if(book.getIsBorrowed()){
                        throw new BusinessException(ResultEnum.BOOK_IS_BORROWED, "图书已被借阅，无法删除");
                    }
                }else{
                    throw new BusinessException(ResultEnum.BOOK_NOT_FOUND, "图书不存在");
                }
            }
            int deletedCount = bookMapper.deleteByIds(bookIds);
            return deletedCount>0;
        } catch (BusinessException e){
            throw e;
        }catch (Exception e) {
            log.error("删除图书时发生系统异常", e);
            throw new BusinessException(ResultEnum.BOOK_DELETE_ERROR, "图书删除失败");
        }
    }
    @Override
    public Book update(BookDTO bookDTO){
        try{

            Book book = lambdaQuery().eq(Book::getBookId, bookDTO.getBookId()).one();
            if (book != null) {
                // 2. 更新图书信息
                book.setBookId(bookDTO.getBookId())
                        .setTitle(bookDTO.getTitle())
                        .setPublisher(bookDTO.getPublisher())
                        .setPublishDate(bookDTO.getPublishDate())
                        .setIsBorrowed(bookDTO.getIsBorrowed());
                // 3. 保存图书
                bookMapper.updateById(book);
                return book;
            }else{
                throw new BusinessException(ResultEnum.BOOK_NOT_FOUND, "图书不存在");
            }


        } catch (BusinessException e) {
        throw e; // 已知业务异常直接抛出
    } catch (Exception e) {
        log.error("更新图书时发生系统异常", e);
        throw new BusinessException(ResultEnum.SYSTEM_ERROR, "图书更新失败");
        }
    }

    @Override
    public List<Book> borrowBooks(List<String> bookIds) {
        try {
            // 1. 查询所有要借阅的图书
            List<Book> books = bookMapper.selectByIds(bookIds);

            // 2. 检查图书是否存在并更新状态
            for (Book book : books) {
                if (book != null) {
                    book.setIsBorrowed(true); // 将图书状态改为已借阅
                } else {
                    throw new BusinessException(ResultEnum.BOOK_NOT_FOUND);
                }
            }

            // 3. 批量更新图书状态
            boolean updated = this.updateBatchById(books);
            if (!updated) {
                log.error("更新图书借阅状态失败，图书信息: {}", books);
                throw new BusinessException(ResultEnum.BOOK_LOAN_ADD_ERROR, "图书借阅失败");
            }

            return books; // 返回更新后的图书列表
        } catch (Exception e) {
            log.error("借阅图书时发生系统异常", e);
            throw new BusinessException(ResultEnum.BOOK_LOAN_ADD_ERROR, "图书借阅失败");
        }
    }
    public List<Book> returnBooks(List<String> bookIds){
        try {
            // 1. 查询所有要借阅的图书
            List<Book> books = bookMapper.selectByIds(bookIds);

            // 2. 检查图书是否存在并更新状态
            for (Book book : books) {
                if (book != null) {
                    book.setIsBorrowed(false);
                } else {
                    throw new BusinessException(ResultEnum.BOOK_NOT_FOUND);
                }
            }
            // 3. 批量更新图书状态
            boolean updated = this.updateBatchById(books);
            if (!updated) {
                log.error("更新图书借阅状态失败，图书信息: {}", books);
                throw new BusinessException(ResultEnum.BOOK_LOAN_DELETE_ERROR, "图书归还失败");
            }

            return books; // 返回更新后的图书列表
        } catch (Exception e) {
            log.error("借阅图书时发生系统异常", e);
            throw new BusinessException(ResultEnum.BOOK_LOAN_ADD_ERROR, "图书借阅失败");
        }
    }

    @Override
    public List<Book> getAllBooks(){
        try{
            return bookMapper.selectList(null);
        }catch (Exception e) {
            log.error("获取图书列表时发生系统异常", e);
            throw new BusinessException(ResultEnum.SYSTEM_ERROR, "获取图书列表失败");
        }
    }

    @Override
    public Book getBookById(String bookId){
        try {
            Book book = bookMapper.selectById(bookId);
            if (book == null) {
                throw new BusinessException(ResultEnum.BOOK_NOT_FOUND, "图书不存在");
            }
            return book;
        } catch (Exception e) {
            log.error("获取图书时发生系统异常", e);
            throw new BusinessException(ResultEnum.SYSTEM_ERROR, "获取图书失败");
        }
    }
}




