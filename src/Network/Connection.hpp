namespace network
{
    template <class T>
    class Connection : public std::enable_shared_from_this<connection<T>> {
        public:
			enum class owner
			{
				server,
				client
			};
            connection() {}
            ~connection() {}
    };
}