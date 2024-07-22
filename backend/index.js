const express = require('express');
const mongoose = require('mongoose');
const bodyParser = require('body-parser');
const Book = require('./routes/book');

const app = express();
app.use(bodyParser.json()); 

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
        await Book.findOneAndDelete({ id: bookId });
        res.status(200).send('Book removed successfully');
    } catch (error) {
        res.status(500).send('Error removing book: ' + error.message);
    }
});

// Find books by title, author, or year
app.get('/api/books', async (req, res) => {
    try {
        const query = req.query;
        const books = await Book.find(query);
        if (books.length > 0) {
            res.status(200).json(books);
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
        res.status(200).json(books);
    } catch (error) {
        res.status(500).send('Error listing books: ' + error.message);
    }
});

// Connect to MongoDB and start the server
mongoose.connect('mongodb+srv://kazuki:89827156@trail-101.9qewedx.mongodb.net/?retryWrites=true&w=majority&appName=trail-101', {
    useNewUrlParser: true,
    useUnifiedTopology: true
}).then(() => {
    const server = app.listen(3000, () => {
        console.log(`\n\n\nServer running on port 3000`);
        console.log(`Process ID: ${process.pid}`);
    });

    const shutdown = async () => {
        console.log('\n\n\n\nShutting down gracefully...');
        try {
            await mongoose.disconnect();
            server.close(() => {
                console.log('\n\nServer closed\n\n');
                process.exit(0);
            });
        } catch (error) {
            console.error('\n\nError during shutdown:', error);
            process.exit(1);
        }
    };

    process.on('SIGINT', shutdown);
    process.on('SIGTERM', shutdown);

}).catch(error => {
    console.error('MongoDB connection error:', error);
});

