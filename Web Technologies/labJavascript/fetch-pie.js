// fetch-pie.js - Implementation for pie-related functionality

document.addEventListener('DOMContentLoaded', function() {
    // Get references to the button and pie cupboard
    const moarPieButton = document.getElementById('moar-pie');
    const pieCupboard = document.getElementById('pie-cupboard');
    
    // Array of pie types
    const pieTypes = [
        'Apple Pie',
        'Cherry Pie',
        'Blueberry Pie',
        'Pumpkin Pie',
        'Pecan Pie',
        'Lemon Meringue Pie',
        'Key Lime Pie',
        'Chocolate Cream Pie',
        'Coconut Cream Pie',
        'Banana Cream Pie'
    ];
    
    // Add event listener to the Moar Pie! button
    if (moarPieButton) {
        moarPieButton.addEventListener('click', function() {
            // Get a random pie from the array
            const randomIndex = Math.floor(Math.random() * pieTypes.length);
            const randomPie = pieTypes[randomIndex];
            
            // Create a new list item for the pie
            const pieItem = document.createElement('li');
            pieItem.textContent = randomPie;
            pieItem.className = 'pie';
            
            // Add the pie to the cupboard
            if (pieCupboard) {
                pieCupboard.appendChild(pieItem);
            }
        });
    }
});
