#ifndef __MOVE_STRUCTURE__
#define __MOVE_STRUCTURE__

#include <fstream>

#include <sdsl/bit_vectors.hpp>

#include "move_row.hpp"
#include "move_query.hpp"

#define END_CHARACTER 0

class MoveStructure {
    public:
        MoveStructure() { }
        MoveStructure(bool verbose_ = false) { verbose = verbose_; }
        MoveStructure(char* input_file, bool bit1_ = false, bool verbose_ = false);

        void build(std::ifstream &bwt_file);
        void query_ms(MoveQuery& mq, bool random);
        std::string reconstruct();

        uint64_t LF(uint64_t row_number);
        uint64_t fast_forward(uint64_t pointer, uint64_t index);
        char compute_char(uint64_t idx);

        uint64_t naive_lcp(uint64_t row1, uint64_t row2);
        uint64_t naive_sa(uint64_t bwt_row);

        uint64_t jump_up(uint64_t idx, char c);
        uint64_t jump_down(uint64_t idx, char c);
        bool jump_randomly(uint64_t& idx, char r_char);
        bool jump_naive_lcp(uint64_t& idx, uint64_t pointer, char r_char, uint64_t& lcp);

        void seralize(char* output_dir);
        void deseralize(char* index_dir);
    private:
        bool bit1;
        std::string bwt_string;
        std::string orig_string;
        bool reconstructed;
        uint64_t length;
        uint64_t r;
        uint64_t end_bwt_row;
        bool verbose;

        std::vector<unsigned char> alphabet;
        std::vector<uint64_t> counts;
        std::vector<uint64_t> alphamap;

        std::vector<sdsl::bit_vector*> occs;
        std::vector<sdsl::rank_support_v<>*> occs_rank;
        sdsl::bit_vector bits;
        sdsl::rank_support_v<> rbits;

        std::vector<MoveRow> rlbwt;
        std::vector<char> rlbwt_chars;
        uint64_t eof_row;
        uint64_t bit1_begin;
        uint64_t bit1_after_eof;
};

#endif