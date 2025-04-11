package org.example.bookmanagement_springboot.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import org.apache.ibatis.annotations.Mapper;
import org.example.bookmanagement_springboot.entity.Book;

/**
* @author DELL
* @description 针对表【book】的数据库操作Mapper
* @createDate 2025-03-27 22:04:17
* @Entity .entity.Book
*/
@Mapper
public interface BookMapper extends BaseMapper<Book> {

}




