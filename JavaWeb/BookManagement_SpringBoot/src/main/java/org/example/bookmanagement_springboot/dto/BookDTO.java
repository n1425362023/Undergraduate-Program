package org.example.bookmanagement_springboot.dto;

import com.fasterxml.jackson.annotation.JsonFormat;
import jakarta.validation.constraints.NotBlank;
import jakarta.validation.constraints.Past;
import lombok.Data;

import java.util.Date;
@Data
public class BookDTO {
    @NotBlank(message = "bookId cannot be empty")
    private String bookId;

    @NotBlank(message = "title cannot be empty")
    private String title;

    @NotBlank(message = "author cannot be empty")
    private String author;

    @NotBlank(message = "publisher cannot be empty")
    private String publisher;
    @Past
    @NotBlank(message = "publishDate cannot be empty")
    @JsonFormat(locale="zh",timezone="GMT+8", pattern="yyyy-MM-dd")
    private Date publishDate;

    private Boolean isBorrowed;
}
