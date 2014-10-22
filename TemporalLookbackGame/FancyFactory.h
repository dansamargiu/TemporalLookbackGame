#pragma once

#include <map>
#include <memory>
#include <functional>
#include <typeindex>

namespace NUtility
{
	class FancyFactory
	{
	private:
		typedef std::string str;
		const char* kNoName = "NO_NAME";

	public:
		FancyFactory() : m_factoryList()
		{
		}

		template <typename I>
		void Unregister(const str& strNamedRegistration)
		{
			const auto tPair = std::make_pair(std::type_index(typeid(I)), strNamedRegistration);
			const auto it = m_factoryList.find(tPair);
			if (it != m_factoryList.end())
			{
				m_factoryList.erase(it);
			}
		}

		template <typename I>
		std::shared_ptr<I> Resolve(const str& strNamedRegistration) const
		{
			const auto tPair = std::make_pair(std::type_index(typeid(I)), strNamedRegistration);
			const auto it = m_factoryList.find(tPair);
			if (it != m_factoryList.end())
			{
				const auto pObj = it->second();
				return std::static_pointer_cast<I>(pObj);
			}

			return nullptr;
		}

		template <typename I>
		void RegisterInstance(const str& strNamedRegistration, std::shared_ptr<I> pInstance)
		{
			auto tFactory = [=] { return pInstance; };
			RegistrationHelper<I>(strNamedRegistration, std::move(tFactory));
		}

		template <typename I, typename T>
		void RegisterType(const str& strNamedRegistration)
		{
			auto tFactory = [&] { return std::make_shared<T>(); };
			RegistrationHelper<I>(strNamedRegistration, std::move(tFactory));
		}

		template <typename I, typename T>
		void RegisterTypeWithFactoryRef(const str& strNamedRegistration)
		{
			auto tFactory = [&] { return std::make_shared<T>(*this); };
			RegistrationHelper<I>(strNamedRegistration, std::move(tFactory));
		}

		template <typename I>
		std::shared_ptr<I> Resolve() const
		{
			return Resolve<I>(kNoName);
		}

		template <typename I>
		void RegisterInstance(std::shared_ptr<I> pInstance)
		{
			RegisterInstance<I>(kNoName, pInstance);
		}

		template <typename I, typename T>
		void RegisterType()
		{
			RegisterType<I, T>(kNoName);
		}

		template <typename I, typename T>
		void RegisterTypeWithFactoryRef()
		{
			RegisterTypeWithFactoryRef<I, T>(kNoName);
		}

	private:
		typedef std::function<std::shared_ptr<void>()> TFactory;
		typedef std::pair<std::type_index, str> TIndex;
		std::map<TIndex, TFactory> m_factoryList;

		template <typename I>
		void RegistrationHelper(const str& strNamedRegistration, TFactory&& tFactory)
		{
			// Always unregister so we don't end up with duplicate entries.
			Unregister<I>(strNamedRegistration);

			// Push the factory onto our list.
			const auto tIndex = std::make_pair(std::type_index(typeid(I)), strNamedRegistration);
			m_factoryList[tIndex] = std::move(tFactory);
		}

		DISALLOW_COPY_AND_ASSIGN(FancyFactory);
	};
}
