import axios from 'axios';

const API_SIGN_URL = 'http://localhost:8080/people'; // Spring Boot 后端地址

export const signin  = async (data : any) => {
  try {
    const response = await axios.post(`${API_SIGN_URL}/login`, data);
    return response.data;
  } catch (error) {
    throw error;
  }
};

export const signup = async (data : any) => {
  try {
    const response = await axios.post(`${API_SIGN_URL}/add`, data);
    return response.data;
  } catch (error) {
    throw error;
  }
}

export const getPeopleInfo  = async (token: string) => {
  try {
    const response = await axios.get(`${API_SIGN_URL}/getPeople/${token}`);
    return response.data;
  } catch (error) {
    throw error;
  }
}


export const updatePeopleInfo  = async (data: any) => {
  try {
    const response = await axios.put(`${API_SIGN_URL}/updateInfo`, data);
    return response.data;
  } catch (error) {
    throw error;
  }
}
export const resetPassword  = async (data: any) => {
  try {
    const response = await axios.put(`${API_SIGN_URL}/updatePassword`, data);
    return response.data;
  } catch (error) {
    throw error;
  }
}

export const getPeopleList  = async () => {
  try {
    const response = await axios.get(`${API_SIGN_URL}/getAll`);
    return response.data;
  } catch (error) {
    throw error;
  }
}
export const getPeople  = async (userId: string) => {
  try {
    const response = await axios.get(`${API_SIGN_URL}/getBorrowedPeople/${userId}`);
    return response.data;
  } catch (error) {
    throw error;
  }
}
export const freezePeople  = async (userId: string ) => {
  try {
    const response = await axios.put(`${API_SIGN_URL}/freezePeople/${userId}`);
    return response.data;
  } catch (error) {
    throw error;
  }
}

export const unfreezePeople  = async (userId: string ) => {
  try {
    const response = await axios.put(`${API_SIGN_URL}/unfreezePeople/${userId}`);
    return response.data;
  } catch (error) {
    throw error;
  }
}

export const deletePeople  = async (userId: string ) => {
  try {
    const response = await axios.delete(`${API_SIGN_URL}/delete/${userId}`);
    return response.data;
  } catch (error) {
    throw error;
  }
}
