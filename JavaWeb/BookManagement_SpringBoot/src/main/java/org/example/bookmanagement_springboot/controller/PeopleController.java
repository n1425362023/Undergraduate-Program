package org.example.bookmanagement_springboot.controller;

import jakarta.validation.Valid;
import lombok.RequiredArgsConstructor;
import org.example.bookmanagement_springboot.common.ApiResponse;
import org.example.bookmanagement_springboot.dto.PeopleDTO;
import org.example.bookmanagement_springboot.entity.People;
import org.example.bookmanagement_springboot.enums.ResultEnum;
import org.example.bookmanagement_springboot.exception.BusinessException;
import org.example.bookmanagement_springboot.service.PeopleService;
import org.example.bookmanagement_springboot.util.JwtUtil;
import org.example.bookmanagement_springboot.validationgroups.LogGroup;
import org.example.bookmanagement_springboot.validationgroups.UpdateInfoGroup;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@CrossOrigin
@RequiredArgsConstructor
@RestController
@RequestMapping("/people")
public class PeopleController {
    private final PeopleService peopleService;

    @PostMapping("/add")
    public ApiResponse<?> addUser(@Valid @RequestBody PeopleDTO peopleDTO) {
        try{
            People people = peopleService.add(peopleDTO);
            return ApiResponse.success(people);
        }catch (BusinessException e){
            return ApiResponse.error(e.getCode());
        }
    }

    @PostMapping("/login")
    public ApiResponse<?> login(@Validated({LogGroup.class}) @RequestBody PeopleDTO peopleDTO){
        try{
            People people = peopleService.login(peopleDTO.getUserId(),peopleDTO.getPasswordHash());
            people.setToken(JwtUtil.generateToken(people.getId(),people.getUserId()));
            return ApiResponse.success(people);
        }catch (BusinessException e){
            return ApiResponse.error(e.getCode());
        }
    }

    @GetMapping("/getAll")
    public ApiResponse<?> getAllPeople(){
        try {
            List<People> list = peopleService.getAllPeople();
            return ApiResponse.success(list);
        }catch (BusinessException e){
            return ApiResponse.error(e.getCode());
        }
    }
    @GetMapping("/getPeople/{token}")
    public ApiResponse<?> getPeopleById(@PathVariable String token){
        try {
            People people = peopleService.getPeopleById(JwtUtil.parseToken(token).getId());
            return ApiResponse.success(people);
        }catch (BusinessException e){
            return ApiResponse.error(e.getCode());
        }
    }
    @GetMapping("/getBorrowedPeople/{userId}")
    public ApiResponse<?> getPeopleByUserId( @PathVariable String userId){
        try {
            People people = peopleService.getByUserId(userId);
            return ApiResponse.success(people);
        }catch (BusinessException e){
            return ApiResponse.error(e.getCode());
        }
    }

    @PutMapping("/updateInfo")
    public ApiResponse<?> updatePeople(@Validated({UpdateInfoGroup.class}) @RequestBody PeopleDTO peopleDTO){
        try{
            People people = peopleService.update(peopleDTO);
            return ApiResponse.success(people);
        }catch (BusinessException e){
            return ApiResponse.error(e.getCode());
        }
    }


    @PutMapping("/updatePassword")
    public ApiResponse<?> updatePassword(@Validated({LogGroup.class}) @RequestBody PeopleDTO peopleDTO){
        try{

            if(peopleService.resetPassword(peopleDTO.getUserId(),peopleDTO.getPasswordHash())){
                return ApiResponse.success(ResultEnum.SUCCESS);
            } else {
                return ApiResponse.error(ResultEnum.USER_PASSWORD_RESET_FAILED);
            }
        }catch (BusinessException e){
            return ApiResponse.error(e.getCode());
        }
    }
    @PutMapping("/freezePeople/{userId}")
    public ApiResponse<?> freezePeople(@PathVariable String userId) {
        try {
            if (peopleService.freezePeople(userId)) {
                return ApiResponse.success(ResultEnum.USER_FROZEN_SUCCESS);
            } else {
                return ApiResponse.error(ResultEnum.USER_FREEZE_FAILED);
            }
        } catch (BusinessException e) {
            return ApiResponse.error(e.getCode());
        }
    }

    @PutMapping("/unfreezePeople/{userId}")
    public ApiResponse<?> unfreezePeople(@PathVariable String userId) {
        try {
            if (peopleService.unfreezePeople(userId)){
                return ApiResponse.success(ResultEnum.USER_UNFROZEN_SUCCESS);
            } else {
                return ApiResponse.error(ResultEnum.USER_UNFREEZE_FAILED);
            }
        } catch (BusinessException e) {
            return ApiResponse.error(e.getCode());
        }
    }
    @DeleteMapping("/delete/{userId}")
    public ApiResponse<?> deletePeople(@Valid @PathVariable String userId) {
        try {
            if(peopleService.deleteById(userId)){
                return ApiResponse.success(ResultEnum.SUCCESS);
            } else {
                return ApiResponse.error(ResultEnum.USER_NOT_FOUND);
            }
        } catch (BusinessException e) {
            return ApiResponse.error(e.getCode());
        }
    }


}
