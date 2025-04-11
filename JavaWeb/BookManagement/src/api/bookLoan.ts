import axios from 'axios';

const API_SIGN_URL = 'http://localhost:8080/bookLoan'; // Spring Boot 后端地址


export const getBookLoanList  = async () => {
    try {
      const response = await axios.get(`${API_SIGN_URL}/getAll`);
      return response.data;
    } catch (error) {
      throw error;
    }
}
export const getBookLoanById = async (userId: string) => {
    try {
      const response = await axios.get(`${API_SIGN_URL}/get/${userId}`);
      return response.data;
    } catch (error) {
      throw error;
    }
}

export const createBookLoan = async (data: any) => {
    try {
      const response = await axios.post(`${API_SIGN_URL}/add`, data);
      return response.data;
    } catch (error) {
      throw error;
    }
}

export const deleteBookLoan = async (bookIds: Array<String>) => {
    try {
      const response = await axios.delete(`${API_SIGN_URL}/deleteBookLoan`,{data: bookIds});
      return response.data;
    } catch (error) {
      throw error;
    }
}

// 明确定义参数类型，避免any
export const updateBookLoan = async (bookLoanId: string, newDueDate: string) => {
  try {
    const response = await axios.put(`${API_SIGN_URL}/update`,null, {
      params: {
          bookLoanId:bookLoanId,      
          dueDate: newDueDate  
      }
    });
    return response.data;
  } catch (error) {
      throw error;
  }
}