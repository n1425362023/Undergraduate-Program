package org.example.bookmanagement_springboot.service;
import com.baomidou.mybatisplus.extension.service.IService;
import org.example.bookmanagement_springboot.dto.BookLoanDTO;
import org.example.bookmanagement_springboot.entity.BookLoan;

import java.util.Date;
import java.util.List;


/**
* @author DELL
* @description 针对表【book_loan】的数据库操作Service
* @createDate 2025-03-27 22:38:48
*/
public interface BookLoanService extends IService<BookLoan> {
    List<BookLoan> addBatch(List<BookLoanDTO> bookLoanDTOs);

    Boolean deleteById(String bookLoanId);

    Boolean deleteBookLoans(List<String> bookIds);

    BookLoan update(String bookLoanId, Date dueDate);

    List<BookLoan> getBookLoansById(String Id);

    List<BookLoan> getAllBookLoans();

}
