package org.example.bookmanagement_springboot.service;

import com.baomidou.mybatisplus.extension.service.IService;
import org.example.bookmanagement_springboot.dto.BookLoanRecordDTO;
import org.example.bookmanagement_springboot.entity.BookLoanRecord;

import java.util.List;

/**
* @author DELL
* @description 针对表【book_loan_record】的数据库操作Service
* @createDate 2025-03-29 16:06:27
*/

public interface BookLoanRecordService extends IService<BookLoanRecord> {

        List <BookLoanRecord> addBatch(List<BookLoanRecordDTO> bookLoanRecordDTOs);

        Boolean deleteByUserId(String userId);

        Boolean deleteByBookLoanRecordId(List<String> bookLoanRecordIds);

        List<BookLoanRecord> getBookLoanRecordsById(String userId,String bookId);

        List<BookLoanRecord> getBookLoanRecordsByUserId(String userId);

        List<BookLoanRecord> getAllBookLoanRecords();
    }
