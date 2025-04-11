package org.example.bookmanagement_springboot.controller;

import jakarta.validation.Valid;
import lombok.RequiredArgsConstructor;
import org.example.bookmanagement_springboot.common.ApiResponse;
import org.example.bookmanagement_springboot.dto.BookLoanDTO;
import org.example.bookmanagement_springboot.dto.BookLoanRecordDTO;
import org.example.bookmanagement_springboot.entity.Book;
import org.example.bookmanagement_springboot.entity.BookLoan;
import org.example.bookmanagement_springboot.entity.BookLoanRecord;
import org.example.bookmanagement_springboot.enums.ResultEnum;
import org.example.bookmanagement_springboot.exception.BusinessException;
import org.example.bookmanagement_springboot.service.BookLoanRecordService;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.*;

import java.util.List;
@CrossOrigin
@RequiredArgsConstructor
@RestController
@RequestMapping("/bookLoanRecord")
public class BookLoanRecordController {
    private final BookLoanRecordService bookLoanRecordService;


    @PostMapping("/addBookLoanRecord")
    public ApiResponse<?> createBookLoanRecord(@Validated @RequestBody List<BookLoanRecordDTO> bookLoanRecordDTOs) {
        try {
            List<BookLoanRecord> bookLoanRecords = bookLoanRecordService.addBatch(bookLoanRecordDTOs);
            return ApiResponse.success(bookLoanRecords);
        } catch (BusinessException e) {
            return ApiResponse.error(e.getCode());
        }
    }


    @DeleteMapping("/delete/{userId}")
    public ApiResponse<?> deleteBookLoanRecord(@PathVariable String userId) {
        try {
            if(bookLoanRecordService.deleteByUserId(userId)){
                return ApiResponse.success(ResultEnum.SUCCESS);
            }else{
                throw new BusinessException(ResultEnum.BOOK_LOAN_RECORD_USERID_DELETE_ERROR);
            }

        } catch (BusinessException e) {
            return ApiResponse.error(e.getCode());
        }
    }
    @DeleteMapping("/deleteBookLoanRecord")
    public ApiResponse<?> deleteBookLoanRecord(@RequestBody List<String> bookLoanRecordIds) {
        try {
            if(bookLoanRecordService.deleteByBookLoanRecordId(bookLoanRecordIds)){
                return ApiResponse.success(ResultEnum.SUCCESS);
            }else{
                throw new BusinessException(ResultEnum.BOOK_LOAN_RECORD_DELETE_ERROR,"借阅记录删除失败");
            }
        } catch (BusinessException e) {
            return ApiResponse.error(e.getCode());
        }
    }
    @GetMapping("/get")
    public ApiResponse<?> getBookLoanRecord(@RequestParam String userId,@RequestParam String bookId){
            try{
                List<BookLoanRecord> bookLoanRecord = bookLoanRecordService.getBookLoanRecordsById(userId,bookId);
                return ApiResponse.success(bookLoanRecord);
            }catch(BusinessException e){
                return ApiResponse.error(e.getCode());
            }
    }
    @GetMapping("/get/{userId}")
    public ApiResponse<?> getBookLoanRecord(@PathVariable String userId){
        try{
            List<BookLoanRecord> bookLoanRecord = bookLoanRecordService.getBookLoanRecordsByUserId(userId);
            return ApiResponse.success(bookLoanRecord);
        }catch(BusinessException e){
            return ApiResponse.error(e.getCode());
        }
    }
    @GetMapping("/getAll")
    public ApiResponse<?> getBookLoanRecordList() {
        try {
            List<BookLoanRecord> bookLoanRecords = bookLoanRecordService.getAllBookLoanRecords();
            return ApiResponse.success(bookLoanRecords);
        } catch (BusinessException e) {
            return ApiResponse.error(e.getCode());
        }

    }
}
