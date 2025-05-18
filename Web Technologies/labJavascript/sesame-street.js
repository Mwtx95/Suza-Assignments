// sesame-street.js - Implementation for cookie-related functionality

// Wait for the document to be fully loaded
document.addEventListener('DOMContentLoaded', function() {
    // Big Bird Yellow: Apply styling to the cookie header when page loads
    const cookieHeader = document.getElementById('cookie-header');
    if (cookieHeader) {
        // Apply yellow styling (Big Bird's color)
        cookieHeader.style.backgroundColor = '#FFDF00'; // Big Bird yellow
        cookieHeader.style.color = '#000000';          // Black text for contrast
        cookieHeader.style.padding = '10px';
        cookieHeader.style.borderRadius = '5px';
        cookieHeader.style.boxShadow = '0 2px 4px rgba(0, 0, 0, 0.2)';
    }
    // Count Chocula: Update the cookie count display
    const cookieJar = document.getElementById('cookie-jar');
    const cookieCount = document.getElementById('cookie-count');
    
    function updateCookieCount() {
        if (cookieJar && cookieCount) {
            const cookies = cookieJar.getElementsByClassName('cookie');
            const numCookies = cookies.length;
            
            // Set the formatted text as requested
            cookieCount.textContent = `${numCookies}! There are ${numCookies} cookie(s) in the cookie jar!`;
            
            // Set the text color to the specified hex value (#f7f16d - a light yellow color)
            cookieCount.style.color = '#f7f16d';
            
            // Add Count Chocula-inspired styling
            cookieCount.style.fontWeight = 'bold';
            cookieCount.style.fontFamily = 'cursive, fantasy';
            cookieCount.style.textShadow = '1px 1px 2px #000';
            cookieCount.style.padding = '8px';
            cookieCount.style.backgroundColor = '#5c2d91'; // Purple background for Count Chocula
            cookieCount.style.borderRadius = '5px';
            cookieCount.style.display = 'inline-block';
            
            // If all cookies are gone, add a message
            if (numCookies === 0) {
                cookieCount.textContent += " Cookie Monster ate them all! Om nom nom!";
            }
        }
    }
    
    // Initial count update
    updateCookieCount();
    
    // Cookie Monster: Remove a cookie every 30 seconds - using 3 seconds for testing
    const cookieInterval = setInterval(function() {
        // Check if there are still cookies in the jar
        if (cookieJar && cookieJar.getElementsByClassName('cookie').length > 0) {
            // Remove the last cookie from the jar
            const lastCookie = cookieJar.getElementsByClassName('cookie')[cookieJar.getElementsByClassName('cookie').length - 1];
            if (lastCookie && lastCookie.parentNode) {
                cookieJar.removeChild(lastCookie);
                
                // Update the cookie count display
                updateCookieCount();
                
                console.log("Cookie removed! Remaining cookies:", cookieJar.getElementsByClassName('cookie').length);
            }
        } else {
            // If no cookies left, we can clear the interval (optional)
            // clearInterval(cookieInterval);
            console.log("No more cookies to remove!");
        }
    }, 30000); 
});
