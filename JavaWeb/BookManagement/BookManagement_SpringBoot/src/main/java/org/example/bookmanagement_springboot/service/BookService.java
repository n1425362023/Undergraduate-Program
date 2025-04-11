package org.example.bookmanagement_springboot.service;

import com.baomidou.mybatisplus.extension.service.IService;
import org.example.bookmanagement_springboot.dto.BookDTO;
import org.example.bookmanagement_springboot.entity.Book;

import java.util.List;

/**
* @author DELL
* @description 针对表【book】的数据库操作Service
* @createDate 2025-03-27 22:04:17
*/
public interface BookService extends IService<Book> {
    Book add(BookDTO bookDTo);

    Boolean deleteById(String bookId);

    Boolean deleteBooks(List<String> bookIds);

    Book update(BookDTO bookDTo);

    List<Book> borrowBooks(List<String> bookIds);

    List<Book> returnBooks(List<String> bookIds);

    List<Book> getAllBooks();

    Book getBookById(String bookId);


}
