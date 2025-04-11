package org.example.bookmanagement_springboot.entity;

import com.baomidou.mybatisplus.annotation.*;

import java.util.Date;
import lombok.Data;
import lombok.experimental.Accessors;

/**
 * @TableName book_loan_record
 */
@TableName(value ="book_loan_record")
@Data
@Accessors(chain = true)
public class BookLoanRecord {
    @TableId(type = IdType.INPUT)
    private String bookLoanRecordId;

    private String userId;

    private String bookId;

    private Date loanDate;

    private Date returnDate;

    private Date dueDate;

    private Boolean isOverdue;

    @TableLogic(value = "0" ,delval = "1")
    private Integer is_deleted;
}