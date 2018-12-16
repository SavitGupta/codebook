import java.math.BigInteger; 
import java.math.BigDecimal; 

// Initialisation
BigInteger A = BigInteger.valueOf(10);
BigInteger B = new BigInteger("10");
BigInteger C, MOD;

C = A.abs();									// C = abs(A)
C = A.add(B);	                       			// C = A + B
C = A.subtract(B);	                  			// C = A - B
C = A.divide(B);                    			// C = A / B
C = A.multiply(B);                  			// C = A * B
C = A.and(B);                       			// C = A & B
C = A.xor(B);                   				// C = A ^ B
C = A.or(B);									// C = A | B
A.compareTo(B) < 0;                 			// A < B
boolean eq = A.equals(B);           			// equality.
C = A.gcd(B);                 					// C = __gcd(A, B)
boolean isprime = A.isProbablePrime(cer);		// if true, it is prime with probability (1 - (1/2)^cer).
C = A.nextProbablePrime();						// C is the next prime after A
int x = A.intValue();							// Integer value of A. Similarly longValue and doubleValue
C = A.min(B);									// C = min(A, B)
C = A.max(B);									// C = max(A, B)
C = A.mod(B);									// C = A % B (0 <= C < B). B should be +ve
C = A.modInverse(B);							// C is mod inverse of A mod B
C = A.modPow(B, MOD);							// C = power(A, B, MOD)
C = A.negate();									// C = -A
C = A.pow(B);									// C = power(A, B)
C = A.remainder(B);								// C = A % B (C can be -ve also). B can be -ve
C = A.sqrt();									// C = int(sqrtl(A))
String s = A.toString(radix);					// s is a string of A in base radix

// Initialisation
BigDecimal A = BigDecimal.valueOf(10);
BigDecimal B = new BigDecimal("10");
BigDecimal C;

C = A.abs();									// C = abs(A)
C = A.add(B, new MathContext(6));      			// C = A + B. MathContext is optional
C = A.subtract(B, new MathContext(6));			// C = A - B. MathContext is optional
C = A.divide(B, scale, new MathContext(6));   	// C = A / B. Scale is no. of decimal places
C = A.divide(B, scale, RoundingMode.CEILING);   // C = A / B. Scale is no. of decimal places
C = A.divideToIntegralValue(B);					// C = int(A / B)
C = A.multiply(B, new MathContext(6));    		// C = A * B. MathContext is optional
A.compareTo(B) < 0;                 			// A < B
boolean eq = A.equals(B);           			// equality.
int x = A.intValue();							// Integer value of A. Similarly longValue and doubleValue
C = A.min(B);									// C = min(A, B)
C = A.max(B);									// C = max(A, B)
C = A.negate();									// C = -A
C = A.pow(B);									// C = power(A, B)
C = A.remainder(B);								// C = A % B (C can be -ve also). B can be -ve
C = A.sqrt();									// C = int(sqrtl(A))
String s = A.toString();						// s is a string of A
C = A.setScale(6);								// C is a bigdecimal of A with scale 6	
C = A.round(new MathContext(4));				// Precision of 4 places(including before decimal places)
