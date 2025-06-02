function validateCreditCard(cardNumber) {
    // Remove any non-digit characters
    const cleanedNumber = cardNumber.replace(/\D/g, '');
    
    // Define validation rules for each card type
    const cardRules = [
        {
            name: 'American Express',
            pattern: /^3[47]\d{13}$/, // Starts with 34 or 37, 15 digits
            validLength: [15]
        },
        {
            name: 'Master Card',
            pattern: /^5[1-5]\d{14}$/, // Starts with 51-55, 16 digits
            validLength: [16]
        },
        {
            name: 'VISA',
            pattern: /^4\d{12}(\d{3})?$/, // Starts with 4, 13 or 16 digits
            validLength: [13, 16]
        },
        {
            name: 'Discover',
            pattern: /^6011\d{11}(\d{1})?$/, // Starts with 6011, 15 or 16 digits
            validLength: [15, 16]
        },
        {
            name: 'Diners Club',
            pattern: /^30[0-5]\d{11}(\d{2})?$/, // Starts with 300-305, 14 or 16 digits
            validLength: [14, 16]
        }
    ];
    
    // Check each card type
    for (const rule of cardRules) {
        if (rule.pattern.test(cleanedNumber) && 
            rule.validLength.includes(cleanedNumber.length)) {
            return { valid: true, type: rule.name };
        }
    }
    
    // If no match found
    return { 
        valid: false, 
        message: 'Invalid credit card number. Please check the number and try again.' 
    };
}

// Example usage:
const result = validateCreditCard('4111111111111111'); // VISA
if (result.valid) {
    console.log(`Valid ${result.type} card`);
} else {
    console.log(result.message);
}

// Test cases
console.log(validateCreditCard('341234567890123'));    // American Express
console.log(validateCreditCard('5112345678901234'));   // Master Card
console.log(validateCreditCard('4123456789012'));      // VISA (13 digits)
console.log(validateCreditCard('4123456789012345'));   // VISA (16 digits)
console.log(validateCreditCard('601112345678901'));    // Discover (15 digits)
console.log(validateCreditCard('6011123456789012'));   // Discover (16 digits)
console.log(validateCreditCard('30512345678901'));     // Diners Club (14 digits)
console.log(validateCreditCard('3051234567890123'));   // Diners Club (16 digits)
console.log(validateCreditCard('1234'));               // Invalid