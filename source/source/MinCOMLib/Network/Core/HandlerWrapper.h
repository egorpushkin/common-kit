#ifndef HANDLERWRAPPER_H__MINCOMLIB__INCLUDED_
#define HANDLERWRAPPER_H__MINCOMLIB__INCLUDED_

namespace MinCOM
{
    
    /**
     * This tool wraps and MinCOM object and holds strong reference to it
     * while any (read or write) asynchronous handler(s) is(are) registered 
     * in the io_service.
     *
     * Usage: see TCPConnection::WriteAsync for an example of code.
     *
     * Rationale:
     * This class is required because it is not enough to override get_pointer
     * routine. Because it is impossible to provide specific wrapper for any
     * object in this case.
     */
    template
    <
        class T
    >
    class HandlerWrapper
    {
    public:
            
        typedef boost::shared_ptr< HandlerWrapper< T > > Ptr_;            
            
        HandlerWrapper(T * thisReference, const ICommonPtr& thisStrong)
            : thisReference_(thisReference)
            , thisStrong_(thisStrong)
        {
        }
            
    private:
            
        /** Provides access for get_pointer routine to thisReference_ field. */
        template< class U > 
        friend inline U * get_pointer(boost::shared_ptr< HandlerWrapper< U > > const & p);
            
        /** 
         * Holds native (not MinCOM) reference to contained object. This 
		 * prevents from ugly workarounds and superfluous runtime castings. 
         */
        T * thisReference_;

        /** Holds strong reference to container object. */
        ICommonPtr thisStrong_; 
            
    };
    
    /**
     * Helper tool that unwraps HandlerWrapper and delegates calls directly to 
	 * the contained object.
     */
    template
    <
        class T
    >
    inline T * get_pointer(boost::shared_ptr< HandlerWrapper< T > > const & p)
    {
        return p.get()->thisReference_;
    }       
    
}

#endif // !HANDLERWRAPPER_H__MINCOMLIB__INCLUDED_
