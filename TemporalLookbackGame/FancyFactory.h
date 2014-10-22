#pragma once
#include <vector>
#include <memory>
#include <functional>
#include <typeindex>

#define INDEX_MATCH(TypeId, strNamedRegistration) \
	std::make_pair(std::type_index(typeid(TypeId)), strNamedRegistration)

namespace NUtility
{	
	class FancyFactory
	{
	public:
		FancyFactory()
		{
		}

		FancyFactory(size_t reservedCapacity)
		{
			m_factoryList.reserve(reservedCapacity);
		}

		template <typename I>
		void Unregister(const std::string& strNamedRegistration)
		{
			// Iterate through list and unregister all types that match this index
			auto it = m_factoryList.begin();
			while (it != m_factoryList.end())
			{
				if (INDEX_MATCH(I, strNamedRegistration) == it->first)
				{
					it = m_factoryList.erase(it);
					return;
				}
				else 
				{
					++it;
				}
			}
		}

		template <typename I>
		std::shared_ptr<I> Resolve(const std::string& strNamedRegistration) const
		{
			// Iterate through our list, looking for type_index of I and named registration combination.
			for (const auto& element : m_factoryList)
			{
				if (INDEX_MATCH(I, strNamedRegistration) == element.first)
				{
					auto pObj = element.second();
					return std::static_pointer_cast<I>(pObj);
				}
			}

			return nullptr;
		}
		
		template <typename I>
		void RegisterInstance(const std::string& strNamedRegistration, std::shared_ptr<I> pInstance)
		{
			auto tFactory = [=] { return pInstance; };
			RegistrationHelper<I>(strNamedRegistration, tFactory);
		}

		template <typename I, typename T>
		void RegisterType(const std::string& strNamedRegistration)
		{
			auto tFactory = [&] { return std::make_shared<T>(); };
			RegistrationHelper<I>(strNamedRegistration, tFactory);
		}

		template <typename I, typename T>
		void RegisterTypeWithFactoryReference(const std::string& strNamedRegistration)
		{
			auto tFactory = [&] { return std::make_shared<T>(*this); };
			RegistrationHelper<I>(strNamedRegistration, tFactory);
		}

		template <typename I>
		std::shared_ptr<I> Resolve() const
		{
			return Resolve<I>("NO_NAME");
		}

		template <typename I>
		void RegisterInstance(std::shared_ptr<I> pInstance)
		{
			RegisterInstance<I>("NO_NAME", pInstance);
		}

		template <typename I, typename T>
		void RegisterType()
		{
			RegisterType<I, T>("NO_NAME");
		}

		template <typename I, typename T>
		void RegisterTypeWithFactoryReference()
		{
			RegisterTypeWithFactoryReference<I, T>("NO_NAME");
		}

	private:
		typedef std::function<std::shared_ptr<void>()> TFactory;
		typedef std::pair<std::type_index, std::string> TIndex;
		std::vector<std::pair<TIndex, TFactory>> m_factoryList;

		template <typename I>
		void RegistrationHelper(const std::string& strNamedRegistration, TFactory&& tFactory)
		{
			// Always unregister so we don't end up with duplicate entries.
			Unregister<I>(strNamedRegistration);

			// Push the factory onto our list.
			auto tIndex = INDEX_MATCH(I, strNamedRegistration);
			auto tStoredPair = std::make_pair(std::move(tIndex), std::move(tFactory));
			m_factoryList.push_back(std::move(tStoredPair));
		}

		DISALLOW_COPY_AND_ASSIGN(FancyFactory);
	};
}

