#ifndef TERMINALPP_MODEL_BRUSH_MODEL_HPP_
#define TERMINALPP_MODEL_BRUSH_MODEL_HPP_

#include "terminalpp/element.hpp"
#include <functional>
#include <memory>

namespace terminalpp { namespace models {

//* =========================================================================
/// \brief A Concept that contains an object that knows all there is to know
/// about being a brush.  In particular, it knows what element should be
/// the fill pattern.
//* =========================================================================
class brush_model
{
public :
    //* =====================================================================
    /// \brief Constructor
    //* =====================================================================
    template <class Model>
    explicit brush_model(Model &&mdl)
      : self_(new model<Model>(std::forward<Model>(mdl)))
    {
    }

    //* =====================================================================
    /// \brief Sets the fill pattern for the brush.
    //* =====================================================================
    void set_fill(terminalpp::element const &fill)
    {
        self_->set_fill(fill);
    }

    //* =====================================================================
    /// \brief Returns the fill pattern for the brush.
    //* =====================================================================
    terminalpp::element get_fill() const
    {
        return self_->get_fill();
    }

private :
    struct concept
    {
        virtual ~concept(){}
        virtual void set_fill(terminalpp::element const &fill) = 0;
        virtual terminalpp::element get_fill() const = 0;
    };

    template <class Model>
    struct model : concept
    {
        model(Model &&mdl)
          : mdl_(std::forward<Model>(mdl))
        {
        }

        void set_fill(terminalpp::element const &fill) override
        {
            mdl_.set_fill(fill);
        }

        terminalpp::element get_fill() const override
        {
            return mdl_.get_fill();
        }

        Model mdl_;
    };

    std::unique_ptr<concept> self_;
};

}}

#endif