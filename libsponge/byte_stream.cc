#include "byte_stream.hh"

// Dummy implementation of a flow-controlled in-memory byte stream.

// For Lab 0, please replace with a real implementation that passes the
// automated checks run by `make check_lab0`.

// You will need to add private members to the class declaration in `byte_stream.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {}

using namespace std;

ByteStream::ByteStream(const size_t capacity)
    :_capacity(capacity),  _eoi(false), _bytes_written(0), _bytes_read(0){}
//ByteStream::ByteStream(const size_t capacity) : _capacity(capacity) {}

size_t ByteStream::write(const string &data) {
    size_t length = min(data.length() , _capacity - _content.size());
    for (size_t i = 0; i < length; ++i) {
        _content.push_back(data[i]);
    }
    _bytes_written += length;
    return length;
}

//! \param[in] len bytes will be copied from the output side of the buffer
string ByteStream::peek_output(const size_t len) const {
//    BYTE data_byte[len];
//    string res;
//    for (size_t i = 0; i < len; ++i) {
//        data_byte[i] = _content[i];
//        string content_byte(reinterpret_cast<char *>(_content[i]));
//        res = res + content_byte;
//    }

    size_t length = min(len, _content.size());
    return string().assign(_content.begin(), _content.begin()+length);
}

//! \param[in] len bytes will be removed from the output side of the buffer
void ByteStream::pop_output(const size_t len) {
    size_t length = min(len, _content.size());
    _bytes_read += length;
    _content.erase(_content.begin(), _content.begin()+length);
}

//! Read (i.e., copy and then pop) the next "len" bytes of the stream
//! \param[in] len bytes will be popped and returned
//! \returns a string
std::string ByteStream::read(const size_t len) {
    string res = peek_output(len);
    pop_output(len);
    return res;
}

void ByteStream::end_input() {
    _eoi = true;
}

bool ByteStream::input_ended() const {
    return _eoi;
}

size_t ByteStream::buffer_size() const {
    return _content.size();
}

bool ByteStream::buffer_empty() const {
    return _content.empty();
}

bool ByteStream::eof() const {
    return buffer_empty() && input_ended();
}

size_t ByteStream::bytes_written() const {
    return _bytes_written;
}

size_t ByteStream::bytes_read() const {
    return _bytes_read;
}

size_t ByteStream::remaining_capacity() const {
    return _capacity - _content.size();
}
