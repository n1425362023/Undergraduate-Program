package org.example.bookmanagement_springboot.util;

import com.google.common.hash.Hashing;

import java.nio.charset.StandardCharsets;

public class Sha256Util {
    public static String encrypt(String password){
        return Hashing.sha256()
                .hashString(password, StandardCharsets.UTF_8)
                .toString();
    }
}
