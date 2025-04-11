package org.example.bookmanagement_springboot.service.impl;

import com.baomidou.mybatisplus.core.conditions.query.LambdaQueryWrapper;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;

import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.example.bookmanagement_springboot.dto.BookLoanDTO;
import org.example.bookmanagement_springboot.entity.BookLoan;
import org.example.bookmanagement_springboot.enums.ResultEnum;
import org.example.bookmanagement_springboot.exception.BusinessException;
import org.example.bookmanagement_springboot.mapper.BookLoanMapper;
import org.example.bookmanagement_springboot.service.BookLoanService;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.Date;
import java.util.List;
import java.util.stream.Collectors;

/**
* @author DELL
* @description 针对表【book_loan】的数据库操作Service实现
* @createDate 2025-03-27 22:38:48
*/
@Service
@Transactional(rollbackFor = Exception.class)
@RequiredArgsConstructor
@Slf4j
public class BookLoanServiceImpl extends ServiceImpl<BookLoanMapper, BookLoan> implements BookLoanService {
    private final BookLoanMapper bookLoanMapper;

    @Override
    public List<BookLoan> addBatch(List<BookLoanDTO> bookLoanDTOs) {
        try {
            // 1. 转换 DTO 列表为实体列表
            List<BookLoan> bookLoans = bookLoanDTOs.stream().map(dto -> {
                return new BookLoan()
                        .setBookId(dto.getBookId())
                        .setUserId(dto.getUserId())
                        .setLoanDate(dto.getLoanDate())
                        .setDueDate(dto.getDueDate());
            }).collect(Collectors.toList());

            // 2. 批量保存借阅记录
            if (!saveBatch(bookLoans)) {
                log.error("借阅记录创建失败，借阅信息: {}", bookLoans);
                throw new BusinessException(ResultEnum.BOOK_LOAN_ADD_ERROR);
            }
            return bookLoans; // 返回成功插入的借阅记录
        } catch (BusinessException e) {
            throw e; // 已知业务异常直接抛出
        } catch (Exception e) {
            log.error("添加借阅记录时发生系统异常", e);
            throw new BusinessException(ResultEnum.SYSTEM_ERROR, "借阅记录创建失败");
        }
    }


    @Override
    public Boolean deleteById(String bookLoanId){
        try {
            BookLoan bookLoan = lambdaQuery().eq(BookLoan::getBookLoanId, bookLoanId).one();
            if (bookLoan != null) {
                bookLoanMapper.deleteById(bookLoan.getBookLoanId());
                return true;
            }else{
                return false;
            }
        } catch (Exception e) {
            log.error("图书归还时发生系统异常", e);
            throw new BusinessException(ResultEnum.BOOK_LOAN_DELETE_ERROR, "图书归还失败");
        }
    }

    @Override
    public Boolean deleteBookLoans(List<String> bookIds) {
        try {
            LambdaQueryWrapper<BookLoan> wrapper = new LambdaQueryWrapper<>();
            wrapper.in(BookLoan::getBookId, bookIds); // 使用bookId字段构建IN条件
            int rowsDeleted = bookLoanMapper.delete(wrapper);
            // 返回是否至少有一条记录被删除
            return rowsDeleted > 0;
        } catch (Exception e) {
            log.error("图书归还时发生系统异常", e);
            throw new BusinessException(ResultEnum.BOOK_LOAN_DELETE_ERROR, "图书归还失败");
        }
    }

    @Override
    public BookLoan update(String bookLoanId, Date dueDate) {
        try {
            BookLoan bookLoan = bookLoanMapper.selectById(bookLoanId);
            if (bookLoan != null) {

                bookLoan.setDueDate(dueDate);
                // 3. 保存图书借阅信息
                bookLoanMapper.updateById(bookLoan);
                return bookLoan;
            } else {
                throw new BusinessException(ResultEnum.BOOK_LOAN_ID_NOT_FOUND, "借阅图书不存在");
            }
        } catch (BusinessException e) {
                throw e; // 已知业务异常直接抛出
        } catch (Exception e) {
            log.error("更新图书借阅发生系统异常", e);
            throw new BusinessException(ResultEnum.SYSTEM_ERROR, "图书借阅更新失败");

        }

    }

    @Override
    public List<BookLoan> getAllBookLoans(){
        try{
            return bookLoanMapper.selectList(null);
        }catch (Exception e) {
            log.error("获取图书借阅列表时发生系统异常", e);
            throw new BusinessException(ResultEnum.SYSTEM_ERROR, "获取图书借阅列表失败");
        }
    }


    @Override
    public List<BookLoan> getBookLoansById(String userId) {
        try {
            LambdaQueryWrapper<BookLoan> bookLoan = new LambdaQueryWrapper<>();
            bookLoan.eq(BookLoan::getUserId, userId);
            return bookLoanMapper.selectList(bookLoan);
        } catch (Exception e) {
            log.error("获取借阅列表时发生系统异常", e);
            throw new BusinessException(ResultEnum.SYSTEM_ERROR, "获取借阅列表失败");
        }
    }




}




