package org.example.bookmanagement_springboot.dto;


import com.fasterxml.jackson.annotation.JsonProperty;
import jakarta.validation.constraints.NotBlank;
import jakarta.validation.constraints.Pattern;
import lombok.Data;
import org.example.bookmanagement_springboot.enums.Gender;
import org.example.bookmanagement_springboot.enums.Role;
import org.example.bookmanagement_springboot.validationgroups.LogGroup;
import org.example.bookmanagement_springboot.validationgroups.UpdateInfoGroup;
import org.example.bookmanagement_springboot.validationgroups.UpdatePasswoedGroup;

@Data
public class PeopleDTO {
    @NotBlank(message = "Token cannot be empty", groups = {UpdatePasswoedGroup.class})
    private String token = null;

    @NotBlank(message = "UserID cannot be empty" , groups = {LogGroup.class,UpdateInfoGroup.class})
    private String userId;

    @NotBlank(message = "Password cannot be empty",groups = {LogGroup.class,UpdatePasswoedGroup.class})
    private String passwordHash;

    @NotBlank(message = "Name cannot be empty", groups = {UpdateInfoGroup.class})
    private String name;

    @JsonProperty("role")
    private Role role;

    @JsonProperty("gender")
    @NotBlank(message = "Gender cannot be empty", groups = {UpdateInfoGroup.class})
    private Gender gender;

    @Pattern(regexp = "^1[3-9]\\d{9}$", message = "Phone number must be 11 digits", groups = {UpdateInfoGroup.class})
    private String phoneNumber;

    private Boolean isFrozen = false;
}
