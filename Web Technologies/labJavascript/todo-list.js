// JavaScript code for to-do list functionality

// Wait for the document to be fully loaded
document.addEventListener('DOMContentLoaded', function() {
    // Get references to all required elements
    const listElement = document.getElementById('list');
    const itemInput = document.getElementById('item');
    const addButton = document.getElementById('add');
    const removeButton = document.getElementById('remove');
    
    // Add button event listener
    addButton.addEventListener('click', function() {
        const itemText = itemInput.value.trim();
        
        // Only add if the input is not empty
        if (itemText !== '') {
            // Create a new list item
            const newItem = document.createElement('li');
            newItem.textContent = itemText;
            
            // Set background color based on alternating pattern
            // Count current items to determine if this should be white or yellow
            const currentItems = listElement.getElementsByTagName('li');
            if (currentItems.length % 2 === 0) {
                // Even number of current items, so new one is white (first item)
                newItem.style.backgroundColor = 'white';
            } else {
                // Odd number of current items, so new one is yellow (second item)
                newItem.style.backgroundColor = 'yellow';
            }
            
            // Add to the list
            listElement.appendChild(newItem);
            
            // Clear the input field
            itemInput.value = '';
        }
    });
    
    // Remove button event listener
    removeButton.addEventListener('click', function() {
        const itemText = itemInput.value.trim().toLowerCase();
        
        // Only proceed if the input is not empty
        if (itemText !== '') {
            // Get all list items
            const items = listElement.getElementsByTagName('li');
            
            // Find the first occurrence of the item (case insensitive)
            let foundIndex = -1;
            for (let i = 0; i < items.length; i++) {
                if (items[i].textContent.toLowerCase() === itemText) {
                    foundIndex = i;
                    break;
                }
            }
            
            // If found, remove it
            if (foundIndex !== -1) {
                listElement.removeChild(items[foundIndex]);
                
                // Update background colors to maintain alternating pattern
                updateBackgroundColors();
            }
            
            // Clear the input field
            itemInput.value = '';
        }
    });
    
    // Function to update background colors after removing an item
    function updateBackgroundColors() {
        const items = listElement.getElementsByTagName('li');
        
        // Reset all background colors according to alternating pattern
        for (let i = 0; i < items.length; i++) {
            if (i % 2 === 0) {
                // Even index (0, 2, 4...) - white background
                items[i].style.backgroundColor = 'white';
            } else {
                // Odd index (1, 3, 5...) - yellow background
                items[i].style.backgroundColor = 'yellow';
            }
        }
    }
});
