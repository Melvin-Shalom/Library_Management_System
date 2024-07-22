const express = require('express');
const mongoose = require('mongoose');
const bodyParser = require('body-parser');
const Book = require('./routes/book'); // Make sure this path is correct

const app = express();
app.use(bodyParser.json()); // Ensure JSON is parsed

// Add a new book
app.post('/api/books', async (req, res) => {
    try {
        const bookData = req.body;
        if (!bookData.id || !bookData.title || !bookData.author || !bookData.year) {
            return res.status(400).send('Missing required fields');
        }
        const newBook = new Book(bookData);
        await newBook.save();
        res.status(201).send('Book added successfully');
    } catch (error) {
        res.status(500).send('Error adding book: ' + error.message);
    }
});

// Remove a book by ID
app.delete('/api/books/:id', async (req, res) => {
    try {
        const bookId = req.params.id;
        const result = await Book.findOneAndDelete({ id: bookId }); // Assuming 'id' is the unique field
        if (result) {
            res.status(200).send('Book removed successfully');
        } else {
            res.status(404).send('Book not found');
        }
    } catch (error) {
        res.status(500).send('Error removing book: ' + error.message);
    }
});

// Find books by title, author, or year
app.get('/api/books', async (req, res) => {
    try {
        const query = req.query;

        // Create a case-insensitive regular expression for the search
        const searchOptions = {};
        if (query.title) {
            searchOptions.title = { $regex: new RegExp(query.title, 'i') }; // Case-insensitive search for title
        }
        if (query.author) {
            searchOptions.author = { $regex: new RegExp(query.author, 'i') }; // Case-insensitive search for author
        }
        if (query.year) {
            searchOptions.year = query.year; // Exact match for year
        }

        const books = await Book.find(searchOptions);

        if (books.length > 0) {
            // Format the books into a readable string
            const formattedBooks = books.map(book => {
                return `
        id: ${book.id}
        title: ${book.title}
        author: ${book.author}
        year: ${book.year}
        `;
            }).join('\n'); // Join all book strings with a newline between each

            // Send the formatted response
            res.status(200).send(formattedBooks);
        } else {
            res.status(404).send('No books found');
        }
    } catch (error) {
        res.status(500).send('Error finding books: ' + error.message);
    }
});

// List books with optional sorting
app.get('/api/books/list', async (req, res) => {
    try {
        const { sort } = req.query;
        let sortOption = {};
        if (sort === 'id') {
            sortOption = { id: 1 }; // Sort by ID
        } else if (sort === 'year') {
            sortOption = { year: 1 }; // Sort by Year
        }
        const books = await Book.find().sort(sortOption);
        
        if (books.length > 0) {
            // Format the books data
            const formattedBooks = books.map(book => ({
                id: book.id,
                title: book.title,
                author: book.author,
                year: book.year
            }));
            
            // Send formatted books as plain text
            const formattedResponse = formattedBooks.map(book => `
        id: ${book.id}
        title: ${book.title}
        author: ${book.author}
        year: ${book.year}
`).join('\n');
            
            res.status(200).send(formattedResponse);
        } else {
            res.status(404).send('No books found');
        }
    } catch (error) {
        res.status(500).send('Error listing books: ' + error.message);
    }
});


console.log(`\n\nNote: Shut the Server using "Ctrl + C" or it will give error when killed incorrectly`)

// Connect to MongoDB and start the server
mongoose.connect('mongodb+srv://kazuki:89827156@trail-101.9qewedx.mongodb.net/?retryWrites=true&w=majority&appName=trail-101', {
}).then(() => {
    const server = app.listen(3000, () => {
        console.log(`\n\n\nServer running on port 3000`);
        console.log(`Process ID: ${process.pid}`);
        console.log(`\n\n\n`);
    });

    const shutdown = async () => {
        try {
            await mongoose.disconnect();
            server.close(() => {
                console.log('\n\n\n\nServer closed\n\n');
                process.exit(0);
            });
        } catch (error) {
            console.error('\n\n\n\nError during shutdown:', error);
            process.exit(1);
        }
    };

    process.on('SIGINT', shutdown);
    process.on('SIGTERM', shutdown);

}).catch(error => {
    console.error('MongoDB connection error:', error);
});

