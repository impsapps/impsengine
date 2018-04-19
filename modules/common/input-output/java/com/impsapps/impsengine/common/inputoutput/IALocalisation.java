package com.impsapps.impsengine.common.inputoutput;

public class IALocalisation {
    private static String localeId = "en";

    public static void setLocaleId(String localeId){
        IALocalisation.localeId = localeId;
    }

    public static String getLocaleId(){
        return localeId;
    }
}
