package org.example.bookmanagement_springboot.enums;

import lombok.Getter;

/**
 * 统一状态码和消息枚举
 */
@Getter
public enum ResultEnum {
    SUCCESS(200, "操作成功"),
    CREATED(201, "资源创建成功"),
    BAD_REQUEST(400, "请求参数错误"),
    UNAUTHORIZED(401, "token无效或已过期"),
    FORBIDDEN(403, "禁止访问"),
    NOT_FOUND(404, "资源不存在"),
    USER_ADD_ERROR(4002, "用户创建失败"),
    USER_PASSWORD_RESET_FAILED(4092, "用户密码重置失败"),
    USER_DELETE_ERROR(4003, "用户删除失败"),
    USER_FROZEN_SUCCESS(4004, "用户冻结成功"),
    USER_UNFROZEN_SUCCESS(4005, "用户解冻成功"),
    USER_FREEZE_FAILED(4006, "用户冻结失败"),
    USER_UNFREEZE_FAILED(4007, "用户解冻失败"),
    USER_FROZEN(4008, "用户已被冻结"),
    CAPTCHA_EXPIRED(4011, "验证码已过期"),
    USER_NOT_FOUND(4012, "用户不存在"),
    USERNAME_CONFLICT(4091, "用户名冲突"),
    BOOK_ADD_ERROR(4004, "图书创建失败"),
    BOOK_DELETE_ERROR(4005, "图书删除失败"),
    BOOK_NOT_FOUND(4013, "图书不存在"),
    BOOK_ID_CONFLICT(4091, "图书编号冲突"),
    BOOK_LOAN_ID_CONFLICT(4092, "借阅编号冲突"),
    BOOK_LOAN_ID_NOT_FOUND(4014, "借阅图书不存在"),
    BOOK_IS_BORROWED(4015, "图书已被借阅"),
    BOOK_LOAN_ADD_ERROR(4006, "图书借阅失败"),
    BOOK_LOAN_DELETE_ERROR(4007, "图书归还失败"),
    BOOK_LOAN_RECORD_ADD_ERROR(4008, "借阅记录添加失败"),
    BOOK_LOAN_RECORD_USERID_DELETE_ERROR(4009, "用户借阅历史不存在"),
    BOOK_LOAN_RECORD_DELETE_ERROR(4009, "借阅记录删除失败"),
    PASSWORD_ERROR(4092, "密码错误"),
    SYSTEM_ERROR(500, "服务器内部错误"),
    INTERNAL_ERROR(5001, "系统内部错误"),
    SERVICE_UNAVAILABLE(503, "服务不可用");

    private final int code;
    private final String message;

    ResultEnum(int code, String message) {
        this.code = code;
        this.message = message;
    }

}