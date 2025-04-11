import sha256 from "crypto-js/sha256";
import Hex from "crypto-js/enc-hex";


export const encrypt = (data: string) => {
  return Hex.stringify(sha256(data));
}