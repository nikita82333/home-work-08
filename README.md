# Bayan
## Search for duplicate files
### Using
```
bayan -d <dirs> [-ex <dirs>] [-l level] [-ms min_file_size] [-fm <file_masks>] [-s block_size] [-h hash_algorithm]
```
- **-d \<dirs>** - list of directories to search.
- **-ex \<dirs>** - list of directories excluded from the search.
- **-l level** - depth level *(0 - only current directory (default))*".
- **-ms min_file_size** - minimum file size in bytes *(1 byte - default value)*.
- **-fm \<file_masks>** - list of file masks to search.
- **-s block_size** - size of the block used to read files in bytes *(8 bytes - default value)*.
- **-h hash_algorithm** - hashing algorithm: *murmurhash2 (default)*, *crc32*, *md5*.