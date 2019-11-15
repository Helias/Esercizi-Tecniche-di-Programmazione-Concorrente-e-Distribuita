/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package reverse;

import javax.jws.WebService;
import javax.jws.WebMethod;
import javax.jws.WebParam;

/**
 *
 * @author archimede
 */
@WebService(serviceName = "reverseServiceServer")
public class reverseServiceServer {

    /**
     * Web service operation
     */
    @WebMethod(operationName = "reverse")
    public String reverse(@WebParam(name = "inputString") String inputString) {
        /* reverse the string and return */
        return new StringBuilder(inputString).reverse().toString();
    }
}
