#pragma once

#include <exception>
#include <utility>
#include <variant>
#include <string>


namespace cls01 {
    struct not_called_exception : std::exception {
    public:
        explicit not_called_exception(std::string msg) : _excMsg(std::move(msg)) {}

    private:
        std::string _excMsg;
    };

    template<class RetType>
    struct worker {
        using Routine = RetType(*)();
        Routine _routine;
        bool _isRoutineCalled = false;
        std::exception_ptr _caughtExc;
        bool _isExcCaught = false;
        std::variant<RetType, std::monostate, std::exception_ptr> _result = std::monostate();

        explicit worker(Routine routine) : _routine(routine) {}

        void run() {
            try {
                _result = _routine();
            }
            catch (...) {
                _isExcCaught = true;
                _caughtExc = std::current_exception();
            }
            _isRoutineCalled = true;
        }

        bool called() { return _isRoutineCalled; }

        // these methods raise not_called_exception if !worker.called():
        RetType get() {
            if (!called()) {
                throw cls01::not_called_exception("Requested result before routine's call");
            }
            return std::visit(
                    [](const auto &result) -> RetType {
                        using T = std::decay_t<decltype(result)>;
                        if constexpr (std::is_same_v<T, RetType>) {
                            return static_cast<RetType>(result);
                        }
                        throw cls01::not_called_exception("Requested result before routine's call");
                    },
                    _result
            );
        }

        std::exception_ptr get_exception() {
            if (!called()) {
                throw cls01::not_called_exception("Requested result before routine's call");
            }
            return _caughtExc;
        }

        bool exception_caught() {
            return _isExcCaught;
        }
    };

}
