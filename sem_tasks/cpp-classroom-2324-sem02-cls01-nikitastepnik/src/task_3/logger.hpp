#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <memory>
#include <utility>
#include <functional>

namespace cls01 {


    template<typename Func, typename Begin, typename End>
    struct LoggingWrapper {
        Func wrappedFunc_;
        Begin log_before;
        End log_after;

        LoggingWrapper(Func func, Begin before, End after)
                : wrappedFunc_(std::move(func)), log_before(std::move(before)), log_after(std::move(after)) {}

        template<typename... Args>
        auto operator()(Args &&... args) {
            std::cout << log_before;
            if constexpr (std::is_same_v<std::invoke_result_t<Func, Args...>, void>) {
                std::apply(wrappedFunc_, std::forward_as_tuple(std::forward<Args>(args)...));
                std::cout << log_after;
            } else {
                auto result = std::apply(wrappedFunc_, std::forward_as_tuple(std::forward<Args>(args)...));
                std::cout << log_after;
                return result;
            }
        }
    };

    template<typename Func, typename Begin, typename End>
    LoggingWrapper<Func, Begin, End> logging_wrapper(Func &&func, Begin &&before, End &&after) {
        return LoggingWrapper<Func, Begin, End>(std::forward<Func>(func), std::forward<Begin>(before),
                                                std::forward<End>(after));
    }

}


