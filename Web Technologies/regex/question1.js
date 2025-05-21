function validateForm() {
    let isValid = true;
    
    // Reset error messages
    document.querySelectorAll('.error').forEach(el => el.textContent = '');
    
    // Name validation (max 20 characters)
    const name = document.getElementById('name').value.trim();
    if (name === '') {
        document.getElementById('nameError').textContent = 'Please enter your name!';
        isValid = false;
    } else if (name.length > 20) {
        document.getElementById('nameError').textContent = 'Name must be 20 characters or less!';
        isValid = false;
    }
    
    // Zip Code validation
    const zip = document.getElementById('zip').value.trim();
    if (zip === '') {
        document.getElementById('zipError').textContent = 'Zip code is required!';
        isValid = false;
    } else if (!/^\d{5}(-\d{4})?$/.test(zip)) {
        document.getElementById('zipError').textContent = 'Please enter a valid zip code!';
        isValid = false;
    }
    
    // Country validation
    const country = document.getElementById('country').value;
    if (country === '') {
        document.getElementById('countryError').textContent = 'Please select a country!';
        isValid = false;
    }
    
    // Gender validation
    const gender = document.querySelector('input[name="gender"]:checked');
    if (!gender) {
        document.getElementById('genderError').textContent = 'Please select your gender!';
        isValid = false;
    }
    
    // Preferences validation (at least 2 colors)
    const preferences = document.querySelectorAll('input[name="preferences"]:checked');
    if (preferences.length < 2) {
        document.getElementById('preferencesError').textContent = 'Please select at least two colors!';
        isValid = false;
    }
    
    // Phone validation
    const phone = document.getElementById('phone').value.trim();
    if (phone === '') {
        document.getElementById('phoneError').textContent = 'Phone number is required!';
        isValid = false;
    } else if (!/^\d{10}$/.test(phone)) {
        document.getElementById('phoneError').textContent = 'Please enter a valid 10-digit phone number!';
        isValid = false;
    }
    
    // Email validation
    const email = document.getElementById('email').value.trim();
    if (email === '') {
        document.getElementById('emailError').textContent = 'Email is required!';
        isValid = false;
    } else if (!/^[^\s@]+@[^\s@]+\.[^\s@]+$/.test(email)) {
        document.getElementById('emailError').textContent = 'Please enter a valid email address!';
        isValid = false;
    }
    
    // Password validation (6-8 characters)
    const password = document.getElementById('password').value;
    if (password === '') {
        document.getElementById('passwordError').textContent = 'Password is required!';
        isValid = false;
    } else if (password.length < 6 || password.length > 8) {
        document.getElementById('passwordError').textContent = 'Password must be 6-8 characters!';
        isValid = false;
    }
    
    // Verify password
    const verifyPassword = document.getElementById('verifyPassword').value;
    if (verifyPassword === '') {
        document.getElementById('verifyPasswordError').textContent = 'Please verify your password!';
        isValid = false;
    } else if (password !== verifyPassword) {
        document.getElementById('verifyPasswordError').textContent = 'Passwords do not match!';
        isValid = false;
    }
    
    return isValid;
}

function clearForm() {
    document.getElementById('myForm').reset();
    document.querySelectorAll('.error').forEach(el => el.textContent = '');
}