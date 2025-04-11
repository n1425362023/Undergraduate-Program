import axios from 'axios';

const API_SIGN_URL = 'http://localhost:8080/book'; // Spring Boot 后端地址


export const getBookList  = async () => {
    try {
      const response = await axios.get(`${API_SIGN_URL}/getAll`);
      return response.data;
    } catch (error) {
      throw error;
    }
}
export const getBook  = async (bookId : String) => {
  try {
    const response = await axios.get(`${API_SIGN_URL}/getBook/${bookId}`);
    return response.data;
  } catch (error) {
    throw error;
  }
}

export const addBook  = async (data: any) => {
    try {
      const response = await axios.post(`${API_SIGN_URL}/add`, data);
      return response.data;
    } catch (error) {
      throw error;
    }
}

export const deleteBooks  = async (bookIds: Array<String>) => {
    try {
      const response = await axios.delete(`${API_SIGN_URL}/deleteBooks`,{data: bookIds});
      return response.data;
    } catch (error) {
      throw error;
    }
}

export const updateBook  = async (data: any) => {
    try {
      const response = await axios.put(`${API_SIGN_URL}/update`, data);
      return response.data;
    } catch (error) {
      throw error;
    }
}

export const borrowBooks  = async (data: any) => {
    try {
      const response = await axios.put(`${API_SIGN_URL}/borrowBooks`, data);
      return response.data;
    } catch (error) {
      throw error;
    }
}

export const returnBooks  = async (data: any) => {
    try {
      const response = await axios.put(`${API_SIGN_URL}/returnBooks`, data);
      return response.data;
    } catch (error) {
      throw error;
    }
}