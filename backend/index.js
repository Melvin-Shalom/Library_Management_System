const express = require('express');
const cors = require('cors');
const bodyParser = require('body-parser');
const db = require('./script/db');
const Book = require('./models/Book');

const app = express();
const port = 3000;

app.use(cors());
app.use(bodyParser.json());

// Add Book
app.post('/api/books', async (req, res) => {
    try {
        const { id, title, author, year } = req.body;
        const newBook = new Book({ id, title, author, year });
        await newBook.save();
        res.status(201).send('Book added');
    } catch (err) {
        res.status(400).send(err.message);
    }
});

// Remove Book
app.delete('/api/books/:id', async (req, res) => {
    try {
        const { id } = req.params;
        await Book.deleteOne({ id });
        res.status(200).send('Book removed');
    } catch (err) {
        res.status(400).send(err.message);
    }
});

// Find Books
app.get('/api/books', async (req, res) => {
    try {
        const { title, author, year } = req.query;
        let query = {};
        if (title) query.title = title;
        if (author) query.author = author;
        if (year) query.year = year;
        const books = await Book.find(query);
        res.status(200).json(books);
    } catch (err) {
        res.status(400).send(err.message);
    }
});

// List Books
app.get('/api/books/list', async (req, res) => {
    try {
        const { sort } = req.query;
        const sortOptions = {};
        if (sort === 'year') {
            sortOptions.year = 1;
        } else if (sort === 'id') {
            sortOptions.id = 1;
        }
        const books = await Book.find().sort(sortOptions);
        res.status(200).json(books);
    } catch (err) {
        res.status(400).send(err.message);
    }
});

app.listen(port, () => {
    console.log(`Server is running on port ${port}`);
});

