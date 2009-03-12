#ifndef LOGSTORAGE_H__MINCOMLIB__INCLUDED_
#define LOGSTORAGE_H__MINCOMLIB__INCLUDED_

namespace MinCOM
{

	class LogStorage
	{
	private:

		typedef struct tagLogLocalData_
		{
			int indent_;
		} 
		LogLocalData_;

		typedef std::map< int, LogLocalData_ > LogData_;

	public:

		static LogStorage& Instance();

		LogStorage();

		int GetIndent();

		void IncreaseIndent();

		void DecreaseIndent();

	private:

		LogLocalData_& GetLocalData();

	private:

		CoreMutex lock_;

		LogData_ logData_;

	};

}

#endif // !LOGSTORAGE_H__MINCOMLIB__INCLUDED_
