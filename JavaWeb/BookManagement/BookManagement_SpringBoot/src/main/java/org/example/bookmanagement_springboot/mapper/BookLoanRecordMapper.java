package org.example.bookmanagement_springboot.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Select;
import org.example.bookmanagement_springboot.entity.BookLoanRecord;

import java.util.List;

/**
* @author DELL
* @description 针对表【book_loan_record】的数据库操作Mapper
* @createDate 2025-03-29 16:06:27
* @Entity .entity.BookLoanRecord
*/
@Mapper
public interface BookLoanRecordMapper extends BaseMapper<BookLoanRecord> {
    @Select("select * from book_loan_record ")
    List<BookLoanRecord> getAllBookLoanRecords();
}




