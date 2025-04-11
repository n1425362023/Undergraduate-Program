package org.example.bookmanagement_springboot.service.impl;

import com.baomidou.mybatisplus.core.conditions.query.LambdaQueryWrapper;
import com.baomidou.mybatisplus.extension.conditions.query.LambdaQueryChainWrapper;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;

import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.example.bookmanagement_springboot.dto.BookLoanRecordDTO;
import org.example.bookmanagement_springboot.entity.BookLoan;
import org.example.bookmanagement_springboot.entity.BookLoanRecord;
import org.example.bookmanagement_springboot.enums.ResultEnum;
import org.example.bookmanagement_springboot.exception.BusinessException;
import org.example.bookmanagement_springboot.mapper.BookLoanRecordMapper;
import org.example.bookmanagement_springboot.service.BookLoanRecordService;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.List;
import java.util.stream.Collectors;

/**
* @author DELL
* @description 针对表【book_loan_record】的数据库操作Service实现
* @createDate 2025-03-29 16:06:27
*/
@Service
@Transactional(rollbackFor = Exception.class)
@RequiredArgsConstructor
@Slf4j
public class BookLoanRecordServiceImpl extends ServiceImpl<BookLoanRecordMapper, BookLoanRecord> implements BookLoanRecordService {
    private final BookLoanRecordMapper bookLoanRecordMapper;

    @Override
    public List<BookLoanRecord> addBatch(List<BookLoanRecordDTO> bookLoanRecordDTOs){
        try{
            // 1. 将DTO转换为实体类
            List<BookLoanRecord> bookLoanRecords =  bookLoanRecordDTOs.stream().map(dto -> {
                return new BookLoanRecord()
                        .setBookLoanRecordId(dto.getBookLoanRecordId())
                        .setBookId(dto.getBookId())
                        .setUserId(dto.getUserId())
                        .setLoanDate(dto.getLoanDate())
                        .setDueDate(dto.getDueDate())
                        .setReturnDate(dto.getReturnDate())
                        .setIsOverdue(dto.getIsOverdue());
            }).collect(Collectors.toList());
            // 2. 批量保存借阅记录
            if (!saveBatch(bookLoanRecords)) {
                log.error("借阅记录创建失败，借阅信息: {}", bookLoanRecords);
                throw new BusinessException(ResultEnum.BOOK_LOAN_RECORD_ADD_ERROR);
            }

            return bookLoanRecords; // 返回成功插入的借阅记录
        } catch (BusinessException e) {
            throw e; // 已知业务异常直接抛出
        } catch (Exception e) {
            log.error("添加借阅历史时发生系统异常", e);
            throw new BusinessException(ResultEnum.SYSTEM_ERROR, "借阅历史添加失败");
        }
    }

    @Override
    public Boolean deleteByUserId(String userId){
        try {
            LambdaQueryChainWrapper<BookLoanRecord> bookLoanRecord= lambdaQuery().eq(BookLoanRecord::getUserId, userId);
            return bookLoanRecordMapper.delete(bookLoanRecord) > 0;
        } catch (Exception e) {
            log.error("借阅历史删除时发生系统异常", e);
            throw new BusinessException(ResultEnum.BOOK_LOAN_DELETE_ERROR, "历史删除失败");
        }
    }

    @Override
    public Boolean deleteByBookLoanRecordId(List<String> bookLoanRecordIds){
        try {
            return bookLoanRecordMapper.deleteByIds(bookLoanRecordIds) > 0;
        } catch (Exception e) {
            log.error("借阅历史删除时发生系统异常", e);
            throw new BusinessException(ResultEnum.BOOK_LOAN_DELETE_ERROR, "历史删除失败");
        }
    }






    /*@Override
    public List<BookLoanRecord> getAllBookLoanRecords(){
        try{
            return bookLoanRecordMapper.selectList(null);
        }catch (Exception e) {
            log.error("获取借阅历史列表时发生系统异常", e);
            throw new BusinessException(ResultEnum.SYSTEM_ERROR, "获取借阅历史列表失败");
        }
    }*/
    @Override
    public List<BookLoanRecord> getAllBookLoanRecords(){
        try{
            return bookLoanRecordMapper.getAllBookLoanRecords();
        }catch (Exception e) {
            log.error("获取借阅历史列表时发生系统异常", e);
            throw new BusinessException(ResultEnum.SYSTEM_ERROR, "获取借阅历史列表失败");
        }
    }


    @Override
    public List<BookLoanRecord> getBookLoanRecordsById(String userId,String bookId){
        try{
            LambdaQueryWrapper<BookLoanRecord>  bookLoanRecord= new LambdaQueryWrapper<>();
            bookLoanRecord.eq(BookLoanRecord::getUserId, userId).eq(BookLoanRecord::getBookId, bookId);
            return bookLoanRecordMapper.selectList(bookLoanRecord);
        }catch (Exception e) {
            log.error("获取借阅历史列表时发生系统异常", e);
            throw new BusinessException(ResultEnum.SYSTEM_ERROR, "获取借阅历史列表失败");
        }
    }

    @Override
    public List<BookLoanRecord> getBookLoanRecordsByUserId(String userId){
        try{
            LambdaQueryWrapper<BookLoanRecord>  bookLoanRecord=  new LambdaQueryWrapper<BookLoanRecord>()
                    .eq(BookLoanRecord::getUserId, userId);
            return bookLoanRecordMapper.selectList(bookLoanRecord);
        }catch (Exception e) {
            log.error("获取借阅历史列表时发生系统异常", e);
            throw new BusinessException(ResultEnum.SYSTEM_ERROR, "获取借阅历史列表失败");
        }
    }
}




