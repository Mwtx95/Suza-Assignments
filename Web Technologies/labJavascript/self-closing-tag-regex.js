// Regular expression to match a self-closing HTML tag
// Requirements:
// 1. Must start with "<"
// 2. Must have a tag name
// 3. Can have 0, 1, or more properties
// 4. Must end with "/>"
// 5. Don't need to worry about whitespace inside the tag

// The regular expression
const selfClosingTagRegex = /<([a-zA-Z][a-zA-Z0-9]*)(\s+[a-zA-Z][a-zA-Z0-9]*(?:=(?:"[^"]*"|'[^']*'|[^\s>]*))?)*\s*\/>/;

// Test function to validate self-closing HTML tags
function validateSelfClosingTag(tag) {
    return selfClosingTagRegex.test(tag);
}

// Test cases
const testCases = [
    { tag: '<img src="foo.jpg" />', expected: true },
    { tag: '<img />', expected: true },
    { tag: '<a href="foo.html" id="stuff" />', expected: true },
    { tag: '</>', expected: false },
    { tag: '<img src= />', expected: false },
    { tag: '<1img />', expected: false },      // Invalid tag name starting with number
    { tag: '<img src="foo.jpg">', expected: false }, // Not self-closing
    { tag: '<img src="foo.jpg', expected: false },   // Missing closing />
    { tag: 'img src="foo.jpg" />', expected: false }, // Missing opening <
    { tag: '<img src="foo.jpg" / >', expected: false } // Space between / and >
];

// Run tests and print results
console.log("Self-Closing HTML Tag Validation Tests:");
testCases.forEach(test => {
    const result = validateSelfClosingTag(test.tag);
    const status = result === test.expected ? 'PASS' : 'FAIL';
    console.log(`${status}: "${test.tag}" - Expected: ${test.expected}, Got: ${result}`);
});

// Explanation of the regex parts:
// <                                      - Matches opening angle bracket
// ([a-zA-Z][a-zA-Z0-9]*)                - Captures tag name (must start with letter, can include letters and numbers)
// (                                 )*   - Group for attributes (0 or more)
//   \s+                                  - At least one whitespace character
//   [a-zA-Z][a-zA-Z0-9]*                - Attribute name (must start with letter)
//   (?:                           )?    - Optional attribute value
//      =                                - Equals sign
//      (?:                        )     - Value options (one of the following)
//         "[^"]*"                       - Double-quoted value
//         |'[^']*'                      - Single-quoted value
//         |[^\s>]*                      - Unquoted value (no whitespace or >)
// \s*                                   - Optional whitespace before closing
// \/>                                   - Self-closing tag end (/ followed by >)
