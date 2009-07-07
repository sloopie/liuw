package name.liuw;

/**
 *
 * @author liuw
 */
/*
 * Triple DES
 * 调用 Java 自身的类实现
 */
import java.security.Key;
import java.security.SecureRandom;
import javax.crypto.Cipher;
import javax.crypto.KeyGenerator;

import sun.misc.BASE64Decoder;
import sun.misc.BASE64Encoder;

/**
 *
 * 使用DES加密与解密,可对byte[],String类型进行加密与解密
 * 密文可使用String,byte[]存储.
 *
 * 方法:
 * void getKey(String strKey)从strKey的字条生成一个Key
 *
 * String getEncString(String strMing)对strMing进行加密,返回String密文
 * String getDesString(String strMi)对strMin进行解密,返回String明文
 *
 *byte[] getEncCode(byte[] byteS)byte[]型的加密
 *byte[] getDesCode(byte[] byteD)byte[]型的解密
 */

public class DES
{
	private Key key;
    private String desType;
    private String strKey;


    public void setDes(String t, String k)
    {
        desType = t;
        strKey = k;
        getKey(k);
    }
    
	public void getKey(String strKey)
	{
		try{
			KeyGenerator _generator = KeyGenerator.getInstance(desType);
			_generator.init(new SecureRandom(strKey.getBytes()));
			this.key = _generator.generateKey();
			_generator=null;
		}catch(Exception e){
			e.printStackTrace();
		}
	}

    public void setDesType(String t)
    {
        desType = t;
    }

	public String getEncString(String strMing)
	{
		byte[] byteMi = null;
		byte[] byteMing = null;
		String strMi = "";
		BASE64Encoder base64en = new BASE64Encoder();
		try
		{
			byteMing = strMing.getBytes("UTF8");
			byteMi = this.getEncCode(byteMing);
			strMi = base64en.encode(byteMi);

		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
		finally
		{
			base64en = null;
			byteMing = null;
			byteMi = null;
		}
		return strMi;
	}

	public String getDesString(String strMi)
	{
		BASE64Decoder base64De = new BASE64Decoder();
		byte[] byteMing = null;
		byte[] byteMi = null;
		String strMing = "";
		try
		{
			byteMi = base64De.decodeBuffer(strMi);
			byteMing = this.getDesCode(byteMi);
			strMing = new String(byteMing, "UTF8");
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
		finally
		{
			base64De = null;
			byteMing = null;
			byteMi = null;
		}
		return strMing;
	}

	private byte[] getEncCode(byte[] byteS)
	{
		byte[] byteFinal = null;
		Cipher cipher;
		try
		{
			cipher = Cipher.getInstance(desType);
			cipher.init(Cipher.ENCRYPT_MODE, key);
			byteFinal = cipher.doFinal(byteS);
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
		finally
		{
			cipher = null;
		}
		return byteFinal;
	}

	private byte[] getDesCode(byte[] byteD)
	{
		Cipher cipher;
		byte[] byteFinal=null;
		try{
			cipher = Cipher.getInstance(desType);
			cipher.init(Cipher.DECRYPT_MODE, key);
			byteFinal = cipher.doFinal(byteD);
		}catch(Exception e){
			e.printStackTrace();
		}finally{
			cipher=null;
		}
		return byteFinal;

	}
/*
	public static void main(String[] args){
		System.out.println("des demo");
		TripleDES des=new TripleDES();
		String key = "KEY";
		String message = "I love you";
		des.getKey(key);
		System.out.println("key="+key);
		String strEnc = des.getEncString(message);
		System.out.println("密文="+strEnc);

		String strDes = des.getDesString(strEnc);
		System.out.println("明文="+strDes);

	}
*/
}


