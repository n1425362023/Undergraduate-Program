package org.example.bookmanagement_springboot.mapper;
import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import org.apache.ibatis.annotations.Mapper;
import org.example.bookmanagement_springboot.entity.BookLoan;

/**
* @author DELL
* @description 针对表【book_loan】的数据库操作Mapper
* @createDate 2025-03-27 22:38:48
* @Entity .entity.BookLoan
*/
@Mapper
public interface BookLoanMapper extends BaseMapper<BookLoan> {

}




