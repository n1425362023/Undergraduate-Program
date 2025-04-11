package org.example.bookmanagement_springboot.service.impl;

import com.baomidou.mybatisplus.extension.conditions.query.LambdaQueryChainWrapper;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;

import lombok.RequiredArgsConstructor;
import org.example.bookmanagement_springboot.dto.PeopleDTO;
import org.example.bookmanagement_springboot.entity.People;
import org.example.bookmanagement_springboot.enums.ResultEnum;
import org.example.bookmanagement_springboot.exception.BusinessException;
import org.example.bookmanagement_springboot.mapper.PeopleMapper;
import org.example.bookmanagement_springboot.service.PeopleService;
import org.example.bookmanagement_springboot.util.JwtUtil;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;
import lombok.extern.slf4j.Slf4j;
import org.example.bookmanagement_springboot.util.Sha256Util;

import java.util.List;

@Service
@Transactional(rollbackFor = Exception.class)
@RequiredArgsConstructor
@Slf4j
public class PeopleServiceImpl extends ServiceImpl<PeopleMapper, People> implements PeopleService {
    private final PeopleMapper peopleMapper;
    @Override
    public People add(PeopleDTO peopleDTO) {
        // 1. 检查用户ID是否存在
        if (lambdaQuery()
                .eq(People::getUserId, peopleDTO.getUserId())
                .exists()) {
            log.warn("用户已存在，用户ID: {}", peopleDTO.getUserId());
            throw new BusinessException(ResultEnum.USERNAME_CONFLICT);
        }
        try {
            // 2. 创建新用户
            People people = new People()
                    .setUserId(peopleDTO.getUserId())
                    .setPasswordHash(Sha256Util.encrypt(peopleDTO.getPasswordHash()))
                    .setName(peopleDTO.getName())
                    .setRole(peopleDTO.getRole())
                    .setGender(peopleDTO.getGender())
                    .setPhoneNumber(peopleDTO.getPhoneNumber());

            // 3. 保存用户
            if (!save(people)) {
                log.error("用户保存失败，用户信息: {}", peopleDTO);
                throw new BusinessException(ResultEnum.USER_ADD_ERROR);
            }

            return people;
        } catch (BusinessException e) {
            throw e; // 已知业务异常直接抛出
        } catch (Exception e) {
            log.error("添加用户时发生系统异常", e);
            throw new BusinessException(ResultEnum.SYSTEM_ERROR, "用户添加失败");
        }
    }

    @Override
    public List<People> getAllPeople(){
        try{
            return peopleMapper.selectList(null);
        }catch (Exception e) {
            log.error("获取用户列表时发生系统异常", e);
            throw new BusinessException(ResultEnum.SYSTEM_ERROR, "获取用户列表失败");
        }
    }


    @Override
    public People login(String userId , String passwordHash) {
        if (lambdaQuery()
                .eq(null!=userId, People::getUserId, userId)
                .exists()) {
            try {
                LambdaQueryChainWrapper<People> lambdaQuery = lambdaQuery().eq(People::getUserId, userId)
                        .eq(null!= passwordHash, People::getPasswordHash, Sha256Util.encrypt(passwordHash));
                if(lambdaQuery.exists()){
                    return lambdaQuery.one();
                }else {
                    throw new BusinessException(ResultEnum.PASSWORD_ERROR, "密码错误");
                }
            }catch (BusinessException e){
                throw e;
            }catch (Exception e) {
                log.error("用户登录时发生系统异常", e);
                throw new BusinessException(ResultEnum.SYSTEM_ERROR, "用户登录失败");
            }
        }else{
            throw new BusinessException(ResultEnum.USER_NOT_FOUND, "用户不存在");
        }
    }


    @Override
    public People update(PeopleDTO peopleDTO) {
        try {
            //JwtUtil.parseToken(peopleDTO.getToken());
            // 2. 更新用户信息
            People people = lambdaQuery().eq(People::getUserId, peopleDTO.getUserId()).one();
            if(people!= null){
                people.setName(peopleDTO.getName())
                        .setGender(peopleDTO.getGender())
                        .setPhoneNumber(peopleDTO.getPhoneNumber());

                // 3. 保存用户
                peopleMapper.updateById(people);
                return people;
            }else{
                log.warn("用户不存在，用户ID: {}", peopleDTO.getUserId());
                throw new BusinessException(ResultEnum.USER_NOT_FOUND);
            }
        } catch (BusinessException e) {
            throw e; // 已知业务异常直接抛出
        } catch (Exception e) {
            log.error("更新用户时发生系统异常", e);
            throw new BusinessException(ResultEnum.SYSTEM_ERROR, "用户更新失败");
        }
    }
    @Override
    public Boolean resetPassword(String userId, String passwordHash) {
        try {
            People people = lambdaQuery().eq(People::getUserId, userId).one();
            if(people!= null){
                people.setPasswordHash(Sha256Util.encrypt(passwordHash));
                peopleMapper.updateById(people);
                return true;
            }else{
                throw new BusinessException(ResultEnum.USER_NOT_FOUND);
            }
        } catch (Exception e) {
            log.error("更新用户密码时发生系统异常", e);
            throw new BusinessException(ResultEnum.SYSTEM_ERROR, "用户密码更新失败");
        }
    }

    @Override
    public Boolean freezePeople(String userId) {
        try {
            People people = lambdaQuery().eq(People::getUserId, userId).one();
            if(people!= null){
                people.setIsFrozen(true);
                peopleMapper.updateById(people);
                return true;
            }else{
                throw new BusinessException(ResultEnum.USER_NOT_FOUND);
            }
        } catch (Exception e) {
            log.error("冻结用户时发生系统异常", e);
            throw new BusinessException(ResultEnum.SYSTEM_ERROR, "用户冻结失败");
        }
    }
    @Override
    public Boolean unfreezePeople(String userId) {
        try {
            People people = lambdaQuery().eq(People::getUserId, userId).one();
            if(people!= null){
                people.setIsFrozen(false);
                peopleMapper.updateById(people);
                return true;
            }else{
                throw new BusinessException(ResultEnum.USER_NOT_FOUND);
            }
        } catch (Exception e) {
            log.error("解冻用户时发生系统异常", e);
            throw new BusinessException(ResultEnum.SYSTEM_ERROR, "用户解冻失败");
        }
    }



    @Override
    public Boolean deleteById(String userId) {
        try {
            People people = lambdaQuery().eq(People::getUserId, userId).one();
            if(people!= null){
                peopleMapper.deleteById(people.getId());
                return true;
            }else{
                throw new BusinessException(ResultEnum.USER_DELETE_ERROR);
            }
        } catch (Exception e) {
            log.error("删除用户时发生系统异常", e);
            throw new BusinessException(ResultEnum.SYSTEM_ERROR, "用户删除失败");
        }
    }


    @Override
    public People getByUserId(String userId) {
        try {

            People people = lambdaQuery().eq(People::getUserId, userId).one();
            if(people== null){
                log.warn("用户不存在，用户ID: {}", userId);
                throw new BusinessException(ResultEnum.USER_NOT_FOUND);
            }else{
                return people;
            }
        } catch (Exception e) {
            log.error("获取用户时发生系统异常", e);
            throw new BusinessException(ResultEnum.SYSTEM_ERROR, "获取用户失败");
        }
    }


    @Override
    public People getPeopleById(String id) {
        if (lambdaQuery()
                .eq(null!=id, People::getId, id)
                .exists()) {
                return peopleMapper.selectById(id);
        }else{
            throw new BusinessException(ResultEnum.USER_NOT_FOUND, "用户不存在");
        }


    }
//    @Override
//    public Boolean deleteByIds(List<String> userIds)  {
//        try {
//            peopleMapper.deleteBatchIds(userIds);
//            return true;
//        } catch (Exception e) {
//            log.error("删除用户时发生系统异常", e);
//            throw new BusinessException(ResultEnum.USER_DELETE_ERROR, "用户删除失败");
//        }
//    }
}
