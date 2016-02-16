#ifndef FIFIDER_MEMORY_HPP
#define FIFIDER_MEMORY_HPP

#define MAGSTR_VAL    "fidev_1"
#define MAGSTR_LEN    7
#define MAGSTR_ADDR   113

class Memory{
    public:
        static Memory& getInstance(void);

        Memory(Memory const&);
        void operator=(Memory const&);

        bool isReady(void);
        void initialize(void);

    private:
         Memory() {};

        void readString(unsigned int start_address, unsigned int end_address, char* data);
        unsigned long readLong(unsigned int start_address, unsigned int end_address);

        void write(unsigned int address, char* data, unsigned int length);

};

#endif //FIFIDER_MEMORY_HPP


// class S
// {
//     public:
//         static S& getInstance()
//         {
//             static S    instance; // Guaranteed to be destroyed.
//                                   // Instantiated on first use.
//             return instance;
//         }
//     private:
//         S() {};                   // Constructor? (the {} brackets) are needed here.
//
//         // C++ 03
//         // ========
//         // Dont forget to declare these two. You want to make sure they
//         // are unacceptable otherwise you may accidentally get copies of
//         // your singleton appearing.
//         S(S const&);              // Don't Implement
//         void operator=(S const&); // Don't implement
//
//         // C++ 11
//         // =======
//         // We can use the better technique of deleting the methods
//         // we don't want.
//     public:
//         S(S const&)               = delete;
//         void operator=(S const&)  = delete;
//
//         // Note: Scott Meyers mentions in his Effective Modern
//         //       C++ book, that deleted functions should generally
//         //       be public as it results in better error messages
//         //       due to the compilers behavior to check accessibility
//         //       before deleted status
// };
