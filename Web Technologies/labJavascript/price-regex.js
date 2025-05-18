// Regular expression to match a price
// Requirements:
// 1. Must start with a dollar sign ($)
// 2. Any amount of numbers can come before the decimal
// 3. Two numbers must follow the decimal
// 4. No other characters allowed

// The regular expression
const priceRegex = /^\$\d*\.\d{2}$/;

// Test function to validate prices
function validatePrice(price) {
    return priceRegex.test(price);
}

// Test cases
const testCases = [
    { price: '$14.99', expected: true },
    { price: '$1234567.00', expected: true },
    { price: '$.90', expected: true },
    { price: '$14', expected: false },
    { price: '$134213.89money', expected: false },
    { price: '$1.1a', expected: false },
    { price: '14.99', expected: false },       // Missing dollar sign
    { price: '$14.999', expected: false },     // Three digits after decimal
    { price: '$14.9', expected: false },       // One digit after decimal
    { price: 'price $14.99', expected: false } // Extra characters before
];

// Run tests and print results
console.log("Price Validation Tests:");
testCases.forEach(test => {
    const result = validatePrice(test.price);
    const status = result === test.expected ? 'PASS' : 'FAIL';
    console.log(`${status}: "${test.price}" - Expected: ${test.expected}, Got: ${result}`);
});

// Explanation of the regex:
// ^ - Start of string
// \$ - Dollar sign (escaped because $ is a special character in regex)
// \d* - Zero or more digits (for before the decimal)
// \. - Decimal point (escaped because . is a special character in regex)
// \d{2} - Exactly 2 digits after the decimal
// $ - End of string

// This ensures:
// 1. The string starts with a dollar sign
// 2. It can have any number of digits before the decimal (including none)
// 3. It must have exactly 2 digits after the decimal
// 4. No other characters are allowed anywhere in the string
