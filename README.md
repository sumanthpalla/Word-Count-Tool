# Own wc Tool

This project implements a custom version of the Unix wc tool in C: ccwc. Like the original wc, it allows you to:

- Count the number of bytes in a file
- Count the number of lines in a file
- Count the number of words in a file
- Count the number of characters in a file

This implementation provides a fun and practical way to explore C/C++ and its capabilities.

## Getting Started

1. Installation

```
git clone 

cd cc-write-your-wc-tool
```

2. Set up

```
make ./ccwc.c test.txt
```

3. Run the command

```
ccwc -c test.txt
```

Note: keep in mind, that the `ccwc` command only works in this directory.

## Usage

This tool helps you analyze a file's size and content. You can use it to count the number of bytes, lines, words, and characters in a file.

| Flag | Description                |
| :--: | :------------------------- |
|  -c  | print the byte count       |
|  -l  | print the lines count      |
|  -w  | print the words count      |
|  -m  | print the characters count |

### Basic Usage

There are two ways to use `ccwc`:

1. File as input:

```bash
ccwc [option] [file]
```

example:

```bash
ccwc -l example.txt
```

2. Standard Input

You can pip date directly to the tool using standard input:

```bash
cat example.txt | ccwc -flag
```

exmaple:

```bash
cat example.txt | ccwc -l
```

### Default Behavior

If you don't specify any flag, the tool will automatically print the byte, line, word counts

example:

```bash
ccwc example.txt

# output:
7137   58159  341836 example.txt
```

### Summary

- Use `flags` to specify which count you want to see.
- Provide a `file path` as input.
- Alternatively, pipe `data` directly using standard input.
- By default, the tool shows `bytes`, `lines`, and `words` count.

## Links

- [Write Your Own wc Tool](https://codingchallenges.fyi/challenges/challenge-wc)
- [Coding Challenges on Substack](https://codingchallenges.substack.com/)
