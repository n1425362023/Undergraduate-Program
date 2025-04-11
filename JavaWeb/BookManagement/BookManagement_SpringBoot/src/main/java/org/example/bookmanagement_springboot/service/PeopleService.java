
package org.example.bookmanagement_springboot.service;

import com.baomidou.mybatisplus.extension.service.IService;
import org.example.bookmanagement_springboot.dto.PeopleDTO;
import org.example.bookmanagement_springboot.entity.People;

import java.util.List;

/**
 * @author DELL
 * @description 针对表【user】的数据库操作Service
 * @createDate 2025-03-15 16:40:42
 */
public interface PeopleService extends IService<People> {
    People add(PeopleDTO userDTO);

    Boolean deleteById(String userId);


    People update(PeopleDTO userDTO);

    Boolean resetPassword(String userId, String passwordHash);

    Boolean freezePeople(String userId);

    Boolean unfreezePeople(String userId);

    People getPeopleById(String userId);

    People login(String userId, String passwordHash);

    List<People> getAllPeople();

    People getByUserId(String userId);
    //Boolean deleteByIds();
}
