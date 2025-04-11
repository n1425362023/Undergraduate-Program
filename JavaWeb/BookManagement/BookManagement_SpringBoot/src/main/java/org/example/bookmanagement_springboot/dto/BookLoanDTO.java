package org.example.bookmanagement_springboot.dto;


import com.fasterxml.jackson.annotation.JsonFormat;
import com.fasterxml.jackson.databind.annotation.JsonSerialize;
import com.fasterxml.jackson.databind.ser.std.ToStringSerializer;
import jakarta.validation.constraints.Future;
import jakarta.validation.constraints.NotBlank;
import lombok.Data;

import java.util.Date;

@Data
public class BookLoanDTO {

    private String bookLoanId;
    @NotBlank(message = "UserId cannot be empty")
    private String userId;
    @NotBlank(message = "BookId cannot be empty")
    private String bookId;

    @JsonFormat(locale="zh",timezone="GMT+8", pattern="yyyy-MM-dd")
    @NotBlank(message = "LoanDate cannot be empty")
    private Date loanDate;
    @JsonFormat(locale="zh",timezone="GMT+8", pattern="yyyy-MM-dd")
    @Future
    @NotBlank(message = "DueDate cannot be empty")
    private Date dueDate;

}
