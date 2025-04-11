import axios from 'axios';

const API_SIGN_URL = 'http://localhost:8080/bookLoanRecord'; // Spring Boot 后端地址



export const getBookLoanRecordList  = async () => {
    try {
      const response = await axios.get(`${API_SIGN_URL}/getAll`);
      return response.data;
    } catch (error) {
      throw error;
    }
}
export const getBookLoanRecord  = async (userId: string) => {
  try {
    const response = await axios.get(`${API_SIGN_URL}/get/${userId}`);
    return response.data;
  } catch (error) {
    throw error;
  }
}
export const createBookLoanRecord = async (data: any) => {
    try {
      const response = await axios.post(`${API_SIGN_URL}/addBookLoanRecord`, data);
      return response.data;
    } catch (error) {
      throw error;
    }
}

export const deleteBookLoanRecordList = async (bookLoanRecordIds: Array<String>) => {
    try {
      const response = await axios.delete(`${API_SIGN_URL}/deleteBookLoanRecord`,{data: bookLoanRecordIds});
      return response.data;
    } catch (error) {
      throw error;
    }
}
