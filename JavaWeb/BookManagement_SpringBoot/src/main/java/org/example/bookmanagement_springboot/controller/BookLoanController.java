package org.example.bookmanagement_springboot.controller;

import jakarta.validation.Valid;
import lombok.RequiredArgsConstructor;
import org.example.bookmanagement_springboot.common.ApiResponse;
import org.example.bookmanagement_springboot.dto.BookLoanDTO;
import org.example.bookmanagement_springboot.entity.Book;
import org.example.bookmanagement_springboot.entity.BookLoan;
import org.example.bookmanagement_springboot.enums.ResultEnum;
import org.example.bookmanagement_springboot.exception.BusinessException;
import org.example.bookmanagement_springboot.service.BookLoanService;
import org.example.bookmanagement_springboot.service.BookService;
import org.example.bookmanagement_springboot.service.PeopleService;
import org.springframework.format.annotation.DateTimeFormat;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.*;

import java.util.Date;
import java.util.List;
@CrossOrigin
@RequiredArgsConstructor
@RestController
@RequestMapping("/bookLoan")
public class BookLoanController {
    private final BookLoanService bookLoanService;
    private final BookService bookService;
    private final PeopleService peopleService;

    @PostMapping("/add")
    public ApiResponse<?> addBookLoan(@Validated @RequestBody List<BookLoanDTO> bookLoanDTOs) {
        try{
            for(BookLoanDTO bookLoanDTO:bookLoanDTOs) {
                if (peopleService.getByUserId(bookLoanDTO.getUserId()) == null) {
                    throw new BusinessException(ResultEnum.USER_NOT_FOUND);
                } else if (peopleService.getByUserId(bookLoanDTO.getUserId()).getIsFrozen()) {
                    throw new BusinessException(ResultEnum.USER_FROZEN);
                } else if (bookService.getBookById(bookLoanDTO.getBookId()) == null) {
                    throw new BusinessException(ResultEnum.BOOK_NOT_FOUND);
                } else if (bookService.getBookById(bookLoanDTO.getBookId()).getIsBorrowed()) {
                    throw new BusinessException(ResultEnum.BOOK_IS_BORROWED);
                }
            }
            List<BookLoan> bookLoans = bookLoanService.addBatch(bookLoanDTOs);
            return ApiResponse.success(bookLoans);
        }catch (BusinessException e){
            return ApiResponse.error(e.getCode());
        }
    }


    @DeleteMapping("/delete/{bookLoanId}")
    public ApiResponse<?> deleteBookLoan(@PathVariable String bookLoanId) {
        try{
            if(bookLoanService.deleteById(bookLoanId)){
                return ApiResponse.success(ResultEnum.SUCCESS);
            }else{
                throw new BusinessException(ResultEnum.BOOK_LOAN_ID_NOT_FOUND);
            }
        }catch (BusinessException e){
            return ApiResponse.error(e.getCode());
        }
    }
    @DeleteMapping("/deleteBookLoan")
    public ApiResponse<?> deleteBooks(@RequestBody List<String> bookIds) {
        try {
            if(bookLoanService.deleteBookLoans(bookIds)){
                return ApiResponse.success(ResultEnum.SUCCESS);
            }else{
                return ApiResponse.error(ResultEnum.BOOK_NOT_FOUND);
            }
        } catch (BusinessException e) {
            return ApiResponse.error(e.getCode());
        }
    }
    @PutMapping("/update")
    public ApiResponse<?> updateBookLoan(@RequestParam String bookLoanId, @RequestParam @DateTimeFormat(pattern = "yyyy-MM-dd") Date dueDate  ) {
        try{
            BookLoan bookLoan = bookLoanService.update(bookLoanId, dueDate);
            return ApiResponse.success(bookLoan);
        }catch (BusinessException e){
            return ApiResponse.error(e.getCode());
        }
    }
    @GetMapping("/get/{userId}")
    public ApiResponse<?> getBookLoan(@PathVariable String userId) {
        try{
            List<BookLoan> bookLoans = bookLoanService.getBookLoansById(userId);
            return ApiResponse.success(bookLoans);
        }catch (BusinessException e){
            return ApiResponse.error(e.getCode());
        }
    }

    @GetMapping("/getAll")
    public ApiResponse<?> getBookLoanList() {
        try {
            List<BookLoan> list = bookLoanService.getAllBookLoans();
            return ApiResponse.success(list);
        } catch (BusinessException e) {
            return ApiResponse.error(e.getCode());
        }
    }
}
