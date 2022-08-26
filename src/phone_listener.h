#include <iostream>

#include <firebase/auth.h>
#include <firebase/app.h>
#include <firebase/future.h>

class PhoneListener: public firebase::auth::PhoneAuthProvider::Listener
{
    public:
        PhoneListener(
            const char* phone_number,
            firebase::auth::Auth* auth
        ): 
            display_message_("Sending SMS with verification code..."),
            display_verification_code_input_box_(false),
            display_resend_sms_button_(false),
            phone_auth_provider_(firebase::auth::PhoneAuthProvider::GetInstance(auth)),
            phone_number_(phone_number)
        {
            SendSMS();
        }

        void OnVerificationCompleted(firebase::auth::Credential credential) override
        {
            // Grab `mutex_` for the scope of `lock`. Callbacks can be called on
            // other threads, so this mutex ensures data access is atomic.
            firebase::MutexLock lock(mutex_);
            credential_ = credential;
        }

        void OnVerificationFailed(const std::string& error) override
        {
            firebase::MutexLock lock(mutex_);
            display_message_ = "Verification failed with error: " + error;
            std::cout << display_message_ << std::endl;
        }

        void OnCodeSent(
            const std::string& verification_id,
            const firebase::auth::PhoneAuthProvider::ForceResendingToken&
            force_resending_token
        ) override
        {
            firebase::MutexLock lock(mutex_);
            verification_id_ = verification_id;
            force_resending_token_ = force_resending_token;
            display_verification_code_input_box_ = true;
            display_message_ = "Waiting for SMS...";
            std::cout << verification_id_ << " " << display_message_ << std::endl;
        }

        void OnCodeAutoRetrievalTimeOut(
            const std::string& verification_id
        ) override
        {
            firebase::MutexLock lock(mutex_);
            display_resend_sms_button_ = true;
        }

        /*
        // Draw the verification GUI on screen and process input events.
        void Draw()
        {
            firebase::MutexLock lock(mutex_);

            // Draw an informative message describing what's currently happening.
            ShowTextBox(display_message_.c_str());

            // Once the time out expires, display a button to resend the SMS.
            // If the button is pressed, call VerifyPhoneNumber again using the
            // force_resending_token_.
            if (display_resend_sms_button_ && !verification_id_.empty()) {
                const bool resend_sms = ShowTextButton("Resend SMS");
                if (resend_sms) {
                    SendSMS();
                }
            }

            // Once the SMS has been sent, allow the user to enter the SMS
            // verification code into a text box. When the user has completed
            // entering it, call GetCredential() to complete the flow.
            if (display_verification_code_input_box_)
            {
                const std::string verification_code = ShowInputBox("Verification code");
                if (!verification_code.empty())
                {
                    credential_ = phone_auth_provider_->GetCredential(
                    verification_id_.c_str(), verification_code.c_str());
                }
            }
        }
        */

        // The phone number verification flow is complete when this returns
        // non-NULL.
        firebase::auth::Credential* credential()
        {
            firebase::MutexLock lock(mutex_);
            return credential_.is_valid() ? &credential_ : nullptr;
        }

    private:
        // GUI-related variables.
        std::string display_message_;
        bool display_verification_code_input_box_;
        bool display_resend_sms_button_;

        // Phone flow related variables.
        firebase::auth::PhoneAuthProvider& phone_auth_provider_;
        std::string phone_number_;
        std::string verification_id_;
        firebase::auth::PhoneAuthProvider::ForceResendingToken force_resending_token_;
        firebase::auth::Credential credential_;

        // Callbacks can be called on other threads, so guard them with a mutex.
        firebase::Mutex mutex_;

        void SendSMS()
        {
            firebase::MutexLock lock(mutex_);
            std::cout << display_message_ << std::endl;
            static const uint32_t kAutoVerifyTimeOut = 2000;
            phone_auth_provider_.VerifyPhoneNumber(
                phone_number_.c_str(), kAutoVerifyTimeOut, &force_resending_token_,
                this
            );
            display_resend_sms_button_ = false;
        }
};
