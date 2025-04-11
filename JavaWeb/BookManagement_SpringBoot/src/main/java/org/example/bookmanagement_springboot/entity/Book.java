package org.example.bookmanagement_springboot.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import java.util.Date;
import lombok.Data;
import lombok.experimental.Accessors;

/**
 * @TableName book
 */
@TableName(value ="book")
@Data
@Accessors(chain = true)
public class Book {
    @TableId(type = IdType.INPUT)
    private String bookId;

    private String title;

    private String author;

    private String publisher;

    private Date publishDate;

    private Boolean isBorrowed;
}