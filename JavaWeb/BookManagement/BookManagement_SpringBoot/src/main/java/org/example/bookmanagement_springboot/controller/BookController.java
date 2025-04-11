package org.example.bookmanagement_springboot.controller;


import jakarta.validation.Valid;
import jakarta.validation.constraints.NotBlank;
import lombok.RequiredArgsConstructor;
import org.example.bookmanagement_springboot.common.ApiResponse;
import org.example.bookmanagement_springboot.dto.BookDTO;
import org.example.bookmanagement_springboot.entity.Book;
import org.example.bookmanagement_springboot.entity.People;
import org.example.bookmanagement_springboot.enums.ResultEnum;
import org.example.bookmanagement_springboot.exception.BusinessException;
import org.example.bookmanagement_springboot.service.BookService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.config.BeanFactoryPostProcessor;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.*;
import java.util.List;

@CrossOrigin
@RequiredArgsConstructor
@RestController
@RequestMapping("/book")
public class BookController {
    private final BookService bookService;
    private final BeanFactoryPostProcessor forceAutoProxyCreatorToUseClassProxying;


    @PostMapping("/add")
    public ApiResponse<?> addBook(@Valid @RequestBody BookDTO bookDTO) {
        try{
            Book book = bookService.add(bookDTO);
            return ApiResponse.success(book);
        }catch (BusinessException e){
            return ApiResponse.error(e.getCode());
        }
    }

    @DeleteMapping("/delete/{BookId}")
    public ApiResponse<?> deleteBook(@Valid @PathVariable String BookId) {
        try {
            if(bookService.deleteById(BookId)){
                return ApiResponse.success(ResultEnum.SUCCESS);
            }else{
                return ApiResponse.error(ResultEnum.BOOK_NOT_FOUND);
            }
        } catch (BusinessException e) {
            return ApiResponse.error(e.getCode());
        }
    }
    @DeleteMapping("/deleteBooks")
    public ApiResponse<?> deleteBooks(@RequestBody List<String> BookIds) {
        try {
            if(bookService.deleteBooks(BookIds)){
                return ApiResponse.success(ResultEnum.SUCCESS);
            }else{
                return ApiResponse.error(ResultEnum.BOOK_DELETE_ERROR);
            }
        } catch (BusinessException e) {
            return ApiResponse.error(e.getCode());
        }
    }
    @PutMapping("/update")
    public ApiResponse<?> updateBook(@Valid @RequestBody BookDTO bookDTO) {
        try {
            Book book = bookService.update(bookDTO);
            return ApiResponse.success(book);
        } catch (BusinessException e) {
            return ApiResponse.error(e.getCode());
        }
    }
    @PutMapping("/borrowBooks")
    public ApiResponse<?> borrowBook( @RequestBody List<String> bookIds) {
        try {
            List<Book> books = bookService.borrowBooks(bookIds);
            return ApiResponse.success(books);
        } catch (BusinessException e) {
            return ApiResponse.error(e.getCode());
        }
    }
    @PutMapping("/returnBooks")
    public ApiResponse<?> returnBook(@RequestBody List<String> bookIds) {
        try {
            List<Book> books = bookService.returnBooks(bookIds);
            return ApiResponse.success(books);
        } catch (BusinessException e) {
            return ApiResponse.error(e.getCode());
        }
    }
    @GetMapping("/getAll")
    public ApiResponse<?> getBookList() {
        try {
            List<Book> list = bookService.getAllBooks();
            return ApiResponse.success(list);
        } catch (BusinessException e) {
            return ApiResponse.error(e.getCode());
        }
    }
    @GetMapping("/getBook/{BookId}")
    public ApiResponse<?> getBook(@PathVariable String BookId) {
        try {
            Book book = bookService.getBookById(BookId);
            return ApiResponse.success(book);
        } catch (BusinessException e) {
            return ApiResponse.error(e.getCode());
        }
    }
}
