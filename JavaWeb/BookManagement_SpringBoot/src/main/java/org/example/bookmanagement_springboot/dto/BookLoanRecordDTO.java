package org.example.bookmanagement_springboot.dto;

import jakarta.validation.constraints.NotBlank;
import lombok.Data;

import java.util.Date;
@Data
public class BookLoanRecordDTO {

    @NotBlank(message = "BookLoanRecordId cannot be empty")
    private String bookLoanRecordId;
    @NotBlank(message = "UserId cannot be empty")
    private String userId;
    @NotBlank(message = "BookId cannot be empty")
    private String bookId;
    @NotBlank(message = "LoanDate cannot be empty")
    private Date loanDate;
    @NotBlank(message = "DueDate cannot be empty")
    private Date dueDate;
    @NotBlank(message = "ReturnDate cannot be empty")
    private Date returnDate;
    private Boolean isOverdue;

}
