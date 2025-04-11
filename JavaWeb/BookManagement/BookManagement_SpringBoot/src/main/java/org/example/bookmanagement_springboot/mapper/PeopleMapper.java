package org.example.bookmanagement_springboot.mapper;
import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import org.apache.ibatis.annotations.Mapper;
import org.example.bookmanagement_springboot.entity.People;

/**
* @author DELL
* @description 针对表【people】的数据库操作Mapper
* @createDate 2025-04-04 22:23:05
* @Entity .entity.People
*/
@Mapper
public interface PeopleMapper extends BaseMapper<People> {

}




