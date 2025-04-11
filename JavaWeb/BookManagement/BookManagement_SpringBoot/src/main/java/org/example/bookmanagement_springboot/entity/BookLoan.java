package org.example.bookmanagement_springboot.entity;

import com.baomidou.mybatisplus.annotation.*;

import java.util.Date;
import lombok.Data;
import lombok.experimental.Accessors;

/**
 * @TableName book_loan
 */
@TableName(value ="book_loan")
@Data
@Accessors(chain = true)
public class BookLoan {
    @TableId(type = IdType.ASSIGN_ID)
    private String bookLoanId;

    private String userId;

    private String bookId;

    private Date loanDate;

    private Date dueDate;



}