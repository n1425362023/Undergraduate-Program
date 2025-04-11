package org.example.bookmanagement_springboot.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableField;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;
import lombok.experimental.Accessors;
import org.example.bookmanagement_springboot.enums.Gender;
import org.example.bookmanagement_springboot.enums.Role;
import org.springframework.expression.spel.ast.Assign;

/**
 * @TableName people
 */
@TableName(value ="people")
@Data
@Accessors(chain = true)
public class People {
    @TableId(type = IdType.ASSIGN_ID)
    private String id;

    private String userId;

    private String passwordHash;

    private String name;

    private Gender gender;

    private Role role;

    private String phoneNumber;

    private Boolean isFrozen;

    @TableField(exist = false)
    private String token;


}
